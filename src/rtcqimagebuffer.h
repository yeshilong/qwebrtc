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

#ifndef RTCQIMAGEBUFFER_H
#define RTCQIMAGEBUFFER_H

#include <QObject>
#include <QSet>
#include <QSize>
#include <QImage>

#include "rtcvideoframebuffer.h"

class RTCQImageBuffer : public IRTCVideoFrameBuffer
{
    Q_OBJECT

  public:
    /**
   * @brief Constructs an RTCQImageBuffer object.
   */
    explicit RTCQImageBuffer(QImage &pixelBuffer, QObject *parent = nullptr);
    explicit RTCQImageBuffer(QImage &pixelBuffer, int adaptedWidth, int adaptedHeight,
                             int cropWidth, int cropHeight, int cropX, int cropY,
                             QObject *parent = nullptr);

    /**
   * @brief Gets the pixel buffer of the video frame buffer.
   * @return The pixel buffer of the video frame buffer.
   */
    QImage &pixelBuffer() const;

    /**
   * @brief Gets the width of the video frame buffer.
   * @return The width of the video frame buffer.
   */
    int width() const;

    /**
   * @brief Gets the height of the video frame buffer.
   * @return The height of the video frame buffer.
   */
    int height() const;

    /**
   * @brief Gets the crop X of the video frame buffer.
   * @return The crop X of the video frame buffer.
   */
    int cropX() const;

    /**
   * @brief Gets the crop Y of the video frame buffer.
   * @return The crop Y of the video frame buffer.
   */
    int cropY() const;

    /**
   * @brief Gets the crop width of the video frame buffer.
   * @return The crop width of the video frame buffer.
   */
    int cropWidth() const;

    /**
   * @brief Gets the crop height of the video frame buffer.
   * @return The crop height of the video frame buffer.
   */
    int cropHeight() const;

    /**
   * @brief Gets the supported pixel formats.
   * @return The supported pixel formats.
   */
    static QVector<int> supportedPixelFormats();

    /**
   * @brief Checks if cropping is required.
   * @return True if cropping is required, false otherwise.
   */
    bool requiresCropping() const;

    /**
   * @brief Checks if scaling to width is required.
   * @param width The width.
   * @param height The height.
   * @return True if scaling to width is required, false otherwise.
   */
    bool requiresScalingToWidth(int width, int height) const;

    /**
   * @brief Gets the buffer size for cropping and scaling to width.
   * @param width The width.
   * @param height The height.
   * @return The buffer size for cropping and scaling to width.
   */
    int bufferSizeForCroppingAndScalingToWidth(int width, int height) const;

    /**
   * @brief Crops and scales to the specified output pixel buffer.
   * @param outputPixelBuffer The output pixel buffer.
   * @param tmpBuffer The temporary buffer.
   * @return True if the operation was successful, false otherwise.
   */
    bool cropAndScaleTo(QImage &outputPixelBuffer, uint8_t *tmpBuffer);

    /**
   * @brief Crops and scales with the specified parameters.
   * @param offsetX The offset X.
   * @param offsetY The offset Y.
   * @param cropWidth The crop width.
   * @param cropHeight The crop height.
   * @param scaleWidth The scale width.
   * @param scaleHeight The scale height.
   * @return The cropped and scaled video frame buffer.
   */
    IRTCVideoFrameBuffer *cropAndScaleWith(int offsetX, int offsetY, int cropWidth, int cropHeight,
                                           int scaleWidth, int scaleHeight);

    /**
   * @brief toI420
   * @return
   */
    RTCI420Buffer *toI420();

  private:
    QImage pixelBuffer_;
    int width_;
    int height_;
    int bufferWidth_;
    int bufferHeight_;
    int cropX_;
    int cropY_;
    int cropWidth_;
    int cropHeight_;

    void cropAndScaleNV12To(QImage &outputImage, uint8_t *tmpBuffer);
    void cropAndScaleARGBTo(QImage &outputImage);
};

#endif // RTCQIMAGEBUFFER_H
