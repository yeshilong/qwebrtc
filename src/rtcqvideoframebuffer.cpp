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

#include "rtcqvideoframebuffer.h"

#include "rtcnativemutablei420buffer.h"

#include "api/video/i420_buffer.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"
#include "rtc_base/checks.h"
#include "rtc_base/logging.h"
#include "third_party/libyuv/include/libyuv.h"

#include <QDebug>

RTCQVideoFrameBuffer::RTCQVideoFrameBuffer(QVideoFrame &pixelBuffer, QObject *parent)
    : IRTCVideoFrameBuffer(parent), pixelBuffer_(pixelBuffer)
{
    cropX_ = 0;
    cropY_ = 0;
    cropWidth_ = pixelBuffer.width();
    cropHeight_ = pixelBuffer.height();
}

RTCQVideoFrameBuffer::RTCQVideoFrameBuffer(QVideoFrame &pixelBuffer, int adaptedWidth,
                                           int adaptedHeight, int cropWidth, int cropHeight,
                                           int cropX, int cropY, QObject *parent)
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

QVideoFrame &RTCQVideoFrameBuffer::pixelBuffer() const
{
    return const_cast<QVideoFrame &>(pixelBuffer_);
}

int RTCQVideoFrameBuffer::width() const
{
    return width_;
}

int RTCQVideoFrameBuffer::height() const
{
    return height_;
}

int RTCQVideoFrameBuffer::cropX() const
{
    return cropX_;
}

int RTCQVideoFrameBuffer::cropY() const
{
    return cropY_;
}

int RTCQVideoFrameBuffer::cropWidth() const
{
    return cropWidth_;
}

int RTCQVideoFrameBuffer::cropHeight() const
{
    return cropHeight_;
}

QVector<int> RTCQVideoFrameBuffer::supportedPixelFormats()
{
    return QVector<int>();
}

bool RTCQVideoFrameBuffer::requiresCropping() const
{
    return cropWidth_ != bufferWidth_ || cropHeight_ != bufferHeight_;
}

bool RTCQVideoFrameBuffer::requiresScalingToWidth(int width, int height) const
{
    return cropWidth_ != width || cropHeight_ != height;
}

int RTCQVideoFrameBuffer::bufferSizeForCroppingAndScalingToWidth(int width, int height) const
{
    QVideoFrameFormat::PixelFormat srcPixelFormat = pixelBuffer_.pixelFormat();

    switch (srcPixelFormat)
    {
    case QVideoFrameFormat::PixelFormat::Format_NV12: {
        int srcChromaWidth = (cropWidth_ + 1) / 2;
        int srcChromaHeight = (cropHeight_ + 1) / 2;
        int dstChromaWidth = (width + 1) / 2;
        int dstChromaHeight = (height + 1) / 2;

        return srcChromaWidth * srcChromaHeight * 2 + dstChromaWidth * dstChromaHeight * 2;
    }
    case QVideoFrameFormat::PixelFormat::Format_BGRA8888:
    case QVideoFrameFormat::PixelFormat::Format_ARGB8888: {
        return 0; // Scaling RGBA frames does not require a temporary buffer.
    }
    default:
        RTC_DCHECK_NOTREACHED() << "Unsupported pixel format.";
        return 0;
    }
}

bool RTCQVideoFrameBuffer::cropAndScaleTo(QVideoFrame &outputPixelBuffer, uint8_t *tmpBuffer)
{
    QVideoFrameFormat::PixelFormat srcPixelFormat = pixelBuffer_.pixelFormat();
    QVideoFrameFormat::PixelFormat dstPixelFormat = outputPixelBuffer.pixelFormat();

    switch (srcPixelFormat)
    {
    case QVideoFrameFormat::PixelFormat::Format_NV12: {
        int dstWidth = outputPixelBuffer.width();
        int dstHeight = outputPixelBuffer.height();
        if (dstWidth > 0 && dstHeight > 0)
        {
            RTC_DCHECK(dstPixelFormat == QVideoFrameFormat::PixelFormat::Format_NV12);
            if (requiresScalingToWidth(dstWidth, dstHeight))
            {
                RTC_DCHECK(tmpBuffer);
            }
            cropAndScaleNV12To(outputPixelBuffer, tmpBuffer);
        }
        break;
    }
    case QVideoFrameFormat::PixelFormat::Format_BGRA8888:
    case QVideoFrameFormat::PixelFormat::Format_ARGB8888: {
        RTC_DCHECK(srcPixelFormat == dstPixelFormat);
        cropAndScaleARGBTo(outputPixelBuffer);
        break;
    }
    default:
        RTC_DCHECK_NOTREACHED() << "Unsupported pixel format.";
    }

    return true;
}

IRTCVideoFrameBuffer *RTCQVideoFrameBuffer::cropAndScaleWith(int offsetX, int offsetY,
                                                             int cropWidth, int cropHeight,
                                                             int scaleWidth, int scaleHeight)
{
    return new RTCQVideoFrameBuffer(pixelBuffer_, width_, height_, cropWidth, cropHeight,
                                    cropX_ + offsetX * cropWidth_ / width_,
                                    cropY_ + offsetY * cropHeight_ / height_);
}

void RTCQVideoFrameBuffer::cropAndScaleNV12To(QVideoFrame &outputPixelBuffer, uint8_t *tmpBuffer)
{
    // Prepare output pointers.
    if (!outputPixelBuffer.map(QVideoFrame::MapMode::ReadWrite))
    {
        qCritical() << "Failed to lock base address";
        return;
    }
    const int dstWidth = outputPixelBuffer.width();
    const int dstHeight = outputPixelBuffer.height();
    uchar *dstY = outputPixelBuffer.bits(0);
    const int dstYStride = outputPixelBuffer.bytesPerLine(0);
    uchar *dstUV = dstY + dstYStride * dstHeight;
    const int dstUVStride = dstYStride;

    // Prepare source pointers.
    if (!pixelBuffer_.map(QVideoFrame::MapMode::ReadOnly))
    {
        qCritical() << "Failed to lock base address";
        return;
    }
    const uchar *srcY = pixelBuffer_.bits(0);
    const int srcYStride = pixelBuffer_.bytesPerLine(0);
    const uchar *srcUV = srcY + srcYStride * pixelBuffer_.height();
    const int srcUVStride = srcYStride;

    // Crop just by modifying pointers.
    srcY += srcYStride * cropY_ + cropX_;
    srcUV += srcUVStride * (cropY_ / 2) + cropX_;

    webrtc::NV12Scale(tmpBuffer, srcY, srcYStride, srcUV, srcUVStride, cropWidth_, cropHeight_,
                      dstY, dstYStride, dstUV, dstUVStride, dstWidth, dstHeight);

    pixelBuffer_.unmap();
    outputPixelBuffer.unmap();
}

void RTCQVideoFrameBuffer::cropAndScaleARGBTo(QVideoFrame &outputVideoFrame)
{
    // Prepare output pointers.
    if (!outputVideoFrame.map(QVideoFrame::MapMode::WriteOnly))
    {
        qCritical() << "Failed to map output video frame.";
        return;
    }
    const int dstWidth = outputVideoFrame.width();
    const int dstHeight = outputVideoFrame.height();

    uchar *dst = outputVideoFrame.bits(0);
    const int dstStride = outputVideoFrame.bytesPerLine(0);

    // Prepare source pointers.
    if (!pixelBuffer_.map(QVideoFrame::MapMode::ReadOnly))
    {
        qCritical() << "Failed to map input video frame.";
        outputVideoFrame.unmap();
        return;
    }
    const uchar *src = pixelBuffer_.bits(0);
    const int srcStride = pixelBuffer_.bytesPerLine(0);

    // Crop just by modifying pointers. Need to ensure that src pointer points to
    // a byte corresponding to the start of a new pixel (byte with B for BGRA) so
    // that libyuv scales correctly.
    const int bytesPerPixel = 4;
    src += srcStride * cropY_ + (cropX_ * bytesPerPixel);

    // Assuming you have libyuv available, you can use ARGBScale like this:
    libyuv::ARGBScale(src, srcStride, cropWidth_, cropHeight_, dst, dstStride, dstWidth, dstHeight,
                      libyuv::kFilterBox);

    pixelBuffer_.unmap();
    outputVideoFrame.unmap();
}

RTCI420Buffer *RTCQVideoFrameBuffer::toI420()
{
    const QVideoFrameFormat::PixelFormat pixelFormat = pixelBuffer_.pixelFormat();

    if (!pixelBuffer_.map(QVideoFrame::MapMode::ReadOnly))
    {
        qCritical() << "Failed to lock base address";
        return nullptr;
    }

    RTCMutableI420Buffer *i420Buffer = new RTCMutableI420Buffer(width_, height_);

    switch (pixelFormat)
    {
    case QVideoFrameFormat::PixelFormat::Format_NV12: {
        const uchar *srcY = pixelBuffer_.bits(0);
        const int srcYStride = pixelBuffer_.bytesPerLine(0);
        const uchar *srcUV = srcY + srcYStride * pixelBuffer_.height();
        const int srcUVStride = srcYStride;

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
        QVideoFrame scaledPixelBuffer;
        QVideoFrame sourcePixelBuffer;
        if (requiresCropping() || requiresScalingToWidth(i420Buffer->width(), i420Buffer->height()))
        {
            // scaledPixelBuffer = QVideoFrame(i420Buffer->width() * i420Buffer->height() * 4,
            //                                 QSize(i420Buffer->width(), i420Buffer->height()),
            //                                 i420Buffer->width() * 4, pixelFormat);
            cropAndScaleTo(scaledPixelBuffer, nullptr);

            if (!scaledPixelBuffer.map(QVideoFrame::MapMode::ReadOnly))
            {
                qCritical() << "Failed to lock base address";
                return nullptr;
            }
            sourcePixelBuffer = scaledPixelBuffer;
        }
        else
        {
            sourcePixelBuffer = pixelBuffer_;
        }
        const uchar *src = sourcePixelBuffer.bits(0);
        const int bytesPerRow = sourcePixelBuffer.bytesPerLine(0);

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

        if (scaledPixelBuffer.isValid())
        {
            scaledPixelBuffer.unmap();
        }
        break;
    }
    default: {
        qCritical() << "Unsupported pixel format.";
        return nullptr;
    }
    }

    pixelBuffer_.unmap();

    return i420Buffer;
}
