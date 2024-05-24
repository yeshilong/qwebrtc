// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rtcqimagebuffer.h"

#include "rtcnativemutablei420buffer.h"

#include "api/video/i420_buffer.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "third_party/libyuv/include/libyuv.h"

#include <QDebug>
#include <QVideoFrame>

RTCQImageBuffer::RTCQImageBuffer(QImage &pixelBuffer, QObject *parent)
    : IRTCVideoFrameBuffer(parent), pixelBuffer_(pixelBuffer)
{
    cropX_ = 0;
    cropY_ = 0;
    cropWidth_ = pixelBuffer.width();
    cropHeight_ = pixelBuffer.height();
}

RTCQImageBuffer::RTCQImageBuffer(QImage &pixelBuffer, int adaptedWidth, int adaptedHeight,
                                 int cropWidth, int cropHeight, int cropX, int cropY,
                                 QObject *parent)
    : IRTCVideoFrameBuffer(parent), pixelBuffer_(pixelBuffer)
{
    width_ = adaptedWidth;
    height_ = adaptedHeight;
    pixelBuffer_ = pixelBuffer;
    bufferWidth_ = pixelBuffer.width();
    bufferHeight_ = pixelBuffer.height();
    cropX_ = cropX & ~1;
    cropY_ = cropY & ~1;
    cropWidth_ = cropWidth;
    cropHeight_ = cropHeight;
}

QImage &RTCQImageBuffer::pixelBuffer() const
{
    return const_cast<QImage &>(pixelBuffer_);
}

int RTCQImageBuffer::width() const
{
    return width_;
}

int RTCQImageBuffer::height() const
{
    return height_;
}

int RTCQImageBuffer::cropX() const
{
    return cropX_;
}

int RTCQImageBuffer::cropY() const
{
    return cropY_;
}

int RTCQImageBuffer::cropWidth() const
{
    return cropWidth_;
}

int RTCQImageBuffer::cropHeight() const
{
    return cropHeight_;
}

QVector<int> RTCQImageBuffer::supportedPixelFormats()
{
    return QVector<int>();
}

bool RTCQImageBuffer::requiresCropping() const
{
    return cropWidth_ != bufferWidth_ || cropHeight_ != bufferHeight_;
}

bool RTCQImageBuffer::requiresScalingToWidth(int width, int height) const
{
    return cropWidth_ != width || cropHeight_ != height;
}

int RTCQImageBuffer::bufferSizeForCroppingAndScalingToWidth(int width, int height) const
{
    QVideoFrameFormat::PixelFormat srcPixelFormat =
        QVideoFrameFormat::pixelFormatFromImageFormat(pixelBuffer_.format());
    switch (srcPixelFormat)
    {
    case QVideoFrameFormat::Format_NV12: {
        int srcChromaWidth = (cropWidth_ + 1) / 2;
        int srcChromaHeight = (cropHeight_ + 1) / 2;
        int dstChromaWidth = (width + 1) / 2;
        int dstChromaHeight = (height + 1) / 2;

        return srcChromaWidth * srcChromaHeight * 2 + dstChromaWidth * dstChromaHeight * 2;
    }
    case QVideoFrameFormat::Format_ARGB8888:
    case QVideoFrameFormat::Format_RGBA8888: {
        return 0; // Scaling RGBA frames does not require a temporary buffer.
    }
    default:
        RTC_DCHECK_NOTREACHED() << "Unsupported pixel format.";
        return 0;
    }
}

bool RTCQImageBuffer::cropAndScaleTo(QImage &outputImage, uint8_t *tmpBuffer)
{
    QVideoFrameFormat::PixelFormat srcPixelFormat =
        QVideoFrameFormat::pixelFormatFromImageFormat(pixelBuffer_.format());
    QVideoFrameFormat::PixelFormat dstPixelFormat =
        QVideoFrameFormat::pixelFormatFromImageFormat(outputImage.format());

    switch (srcPixelFormat)
    {
    case QVideoFrameFormat::PixelFormat::Format_NV12: {
        int dstWidth = outputImage.width();
        int dstHeight = outputImage.height();
        if (dstWidth > 0 && dstHeight > 0)
        {
            Q_ASSERT(dstPixelFormat == QVideoFrameFormat::PixelFormat::Format_NV12);
            if (this->requiresScalingToWidth(dstWidth, dstHeight))
            {
                Q_ASSERT(tmpBuffer);
            }
            this->cropAndScaleNV12To(outputImage, tmpBuffer);
        }
        break;
    }
    case QVideoFrameFormat::PixelFormat::Format_ARGB8888:
    case QVideoFrameFormat::PixelFormat::Format_RGBA8888: {
        Q_ASSERT(srcPixelFormat == dstPixelFormat);
        this->cropAndScaleARGBTo(outputImage);
        break;
    }
    default: {
        RTC_DCHECK_NOTREACHED() << "Unsupported pixel format.";
        return false;
    }
    }

    return true;
}

IRTCVideoFrameBuffer *RTCQImageBuffer::cropAndScaleWith(int offsetX, int offsetY, int cropWidth,
                                                        int cropHeight, int scaleWidth,
                                                        int scaleHeight)
{
    return new RTCQImageBuffer(pixelBuffer_, width_, height_, cropWidth, cropHeight,
                               cropX_ + offsetX * cropWidth_ / width_,
                               cropY_ + offsetY * cropHeight_ / height_);
}

void RTCQImageBuffer::cropAndScaleNV12To(QImage &outputBuffer, uint8_t *tmpBuffer)
{
    // Prepare output pointers.
    int dstWidth = outputBuffer.width();
    int dstHeight = outputBuffer.height();

    uchar *dstY = outputBuffer.bits();
    int dstYStride = outputBuffer.bytesPerLine();

    uchar *dstUV = outputBuffer.bits() + dstYStride * dstHeight;
    int dstUVStride = outputBuffer.bytesPerLine();

    // Prepare source pointers.
    const uchar *srcY = pixelBuffer_.bits();
    int srcYStride = pixelBuffer_.bytesPerLine();

    const uchar *srcUV = pixelBuffer_.bits() + srcYStride * pixelBuffer_.height();
    int srcUVStride = pixelBuffer_.bytesPerLine();

    // Crop just by modifying pointers.
    srcY += srcYStride * cropY_ + cropX_;
    srcUV += srcUVStride * (cropY_ / 2) + cropX_;

    webrtc::NV12Scale(tmpBuffer, srcY, srcYStride, srcUV, srcUVStride, cropWidth_, cropHeight_,
                      dstY, dstYStride, dstUV, dstUVStride, dstWidth, dstHeight);
}

void RTCQImageBuffer::cropAndScaleARGBTo(QImage &outputImage)
{
    // Prepare output pointers.
    int dstWidth = outputImage.width();
    int dstHeight = outputImage.height();

    uchar *dst = outputImage.bits();
    int dstStride = outputImage.bytesPerLine();

    // Prepare source pointers.
    const uchar *src = pixelBuffer_.bits();
    int srcStride = pixelBuffer_.bytesPerLine();

    // Crop just by modifying pointers. Need to ensure that src pointer points to a byte corresponding
    // to the start of a new pixel (byte with B for BGRA) so that libyuv scales correctly.
    const int bytesPerPixel = 4;
    src += srcStride * cropY_ + (cropX_ * bytesPerPixel);

    // QImage::Format_ARGB32 corresponds to libyuv::FOURCC_ARGB
    libyuv::ARGBScale(src, srcStride, cropWidth_, cropHeight_, dst, dstStride, dstWidth, dstHeight,
                      libyuv::kFilterBox);
}

RTCI420Buffer *RTCQImageBuffer::toI420()
{
    QImage::Format imageFormat = pixelBuffer_.format();
    QVideoFrameFormat::PixelFormat pixelFormat =
        QVideoFrameFormat::pixelFormatFromImageFormat(pixelBuffer_.format());

    RTCMutableI420Buffer *i420Buffer = new RTCMutableI420Buffer(this->width(), this->height());

    switch (pixelFormat)
    {
    case QVideoFrameFormat::PixelFormat::Format_NV12: {
        const uchar *srcY = pixelBuffer_.bits();
        int srcYStride = pixelBuffer_.bytesPerLine();
        const uchar *srcUV = srcY + pixelBuffer_.height() * srcYStride;
        int srcUVStride = srcYStride;

        // Crop just by modifying pointers.
        srcY += srcYStride * cropY_ + cropX_;
        srcUV += srcUVStride * (cropY_ / 2) + cropX_;

        // TODO: Use a frame buffer pool.
        webrtc::NV12ToI420Scaler nv12ToI420Scaler;
        nv12ToI420Scaler.NV12ToI420Scale(
            srcY, srcYStride, srcUV, srcUVStride, cropWidth_, cropHeight_,
            i420Buffer->mutableDataY(), i420Buffer->strideY(), i420Buffer->mutableDataU(),
            i420Buffer->strideU(), i420Buffer->mutableDataV(), i420Buffer->strideV(),
            i420Buffer->width(), i420Buffer->height());
        break;
    }
    case QVideoFrameFormat::PixelFormat::Format_ARGB8888:
    case QVideoFrameFormat::PixelFormat::Format_BGRA8888: {
        QImage scaledPixelBuffer;
        QImage sourcePixelBuffer;
        if (requiresCropping() || requiresScalingToWidth(i420Buffer->width(), i420Buffer->height()))
        {
            scaledPixelBuffer = QImage(i420Buffer->width(), i420Buffer->height(), imageFormat);
            cropAndScaleTo(scaledPixelBuffer, nullptr);

            sourcePixelBuffer = scaledPixelBuffer;
        }
        else
        {
            sourcePixelBuffer = pixelBuffer_;
        }
        const uchar *src = sourcePixelBuffer.bits();
        int bytesPerRow = sourcePixelBuffer.bytesPerLine();

        if (pixelFormat == QVideoFrameFormat::PixelFormat::Format_ARGB8888)
        {
            // Corresponds to libyuv::FOURCC_ARGB
            libyuv::ARGBToI420(src, bytesPerRow, i420Buffer->mutableDataY(), i420Buffer->strideY(),
                               i420Buffer->mutableDataU(), i420Buffer->strideU(),
                               i420Buffer->mutableDataV(), i420Buffer->strideV(),
                               i420Buffer->width(), i420Buffer->height());
        }
        else if (pixelFormat == QVideoFrameFormat::PixelFormat::Format_BGRA8888)
        {
            // Corresponds to libyuv::FOURCC_BGRA
            libyuv::BGRAToI420(src, bytesPerRow, i420Buffer->mutableDataY(), i420Buffer->strideY(),
                               i420Buffer->mutableDataU(), i420Buffer->strideU(),
                               i420Buffer->mutableDataV(), i420Buffer->strideV(),
                               i420Buffer->width(), i420Buffer->height());
        }
        break;
    }
    default: {
        qFatal("Unsupported pixel format.");
        return nullptr;
    }
    }

    return i420Buffer;
}
