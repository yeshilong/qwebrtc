/*
 * Copyright (C) 2024 Deltarion Systems
 *
 * This software is licensed under the terms of the GNU Lesser
 * General Public License (LGPL) version 3 as published by the Free
 * Software Foundation. This license is available at:
 * https://www.gnu.org/licenses/lgpl-3.0.html
 *
 * You are free to modify and distribute this software under the
 * terms of the LGPLv3 license. You are required to make the source
 * code of any modifications available under the same license.
 */
#ifndef RTCQVIDEOFRAMEBUFFER_H
#define RTCQVIDEOFRAMEBUFFER_H

#include <QObject>
#include <QSet>
#include <QSize>
#include <QVideoFrame>

#include "rtcvideoframebuffer.h"

class RTCQVideoFrameBuffer : public IRTCVideoFrameBuffer
{
    Q_OBJECT

  public:
    /**
   * @brief Constructs an RTCQVideoFrameBuffer object.
   */
    explicit RTCQVideoFrameBuffer(QVideoFrame &pixelBuffer, QObject *parent = nullptr);
    explicit RTCQVideoFrameBuffer(QVideoFrame &pixelBuffer, int adaptedWidth, int adaptedHeight,
                                  int cropWidth, int cropHeight, int cropX, int cropY,
                                  QObject *parent = nullptr);

    /**
   * @brief Gets the pixel buffer of the video frame buffer.
   * @return The pixel buffer of the video frame buffer.
   */
    QVideoFrame &pixelBuffer() const;

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
    bool cropAndScaleTo(QVideoFrame &outputPixelBuffer, uint8_t *tmpBuffer);

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
    QVideoFrame pixelBuffer_;
    int width_;
    int height_;
    int bufferWidth_;
    int bufferHeight_;
    int cropX_;
    int cropY_;
    int cropWidth_;
    int cropHeight_;

    void cropAndScaleNV12To(QVideoFrame &outputImage, uint8_t *tmpBuffer);
    void cropAndScaleARGBTo(QVideoFrame &outputImage);
};

#endif // RTCQVIDEOFRAMEBUFFER_H
