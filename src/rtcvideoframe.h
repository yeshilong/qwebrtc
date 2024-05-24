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

#ifndef RTCVIDEOFRAME_H
#define RTCVIDEOFRAME_H

#include <QObject>
#include <QImage>
#include <QSize>

#include "rtctypes.h"

class IRTCVideoFrameBuffer;
/**
 * @brief The RTCVideoFrame class.
 */
class RTCVideoFrame : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoFrame object.
     */
    RTCVideoFrame(QObject *parent = nullptr) = delete;

    /**
     * @brief Initialize an RTCVideoFrame from a frame buffer, rotation, and timestamp.
     * @param frameBuffer The frame buffer.
     * @param rotation The rotation.
     * @param timeStampNs The timestamp in nanoseconds.
     */
    explicit RTCVideoFrame(std::shared_ptr<IRTCVideoFrameBuffer> frameBuffer,
                           RTCVideoRotation rotation, qint64 timeStampNs);

    /**
     * @brief Initialize an RTCVideoFrame from a pixel buffer, rotation, and timestamp.
     * @param pixelBuffer The pixel buffer.
     * @param rotation The rotation.
     * @param timeStampNs The timestamp in nanoseconds.
     */
    RTCVideoFrame(QImage *pixelBuffer, RTCVideoRotation rotation, qint64 timeStampNs);

    /**
     * @brief Initialize an RTCVideoFrame from a pixel buffer combined with cropping and
     * scaling. Cropping will be applied first on the pixel buffer, followed by
     * scaling to the final resolution of scaledWidth x scaledHeight.
     * @param pixelBuffer The pixel buffer.
     * @param scaledSize The final resolution after scaling.
     * @param cropRect The rectangle to crop from the pixel buffer.
     * @param rotation The rotation.
     * @param timeStampNs The timestamp in nanoseconds.
     */
    RTCVideoFrame(QImage *pixelBuffer, const QSize &scaledSize, const QRect &cropRect,
                  RTCVideoRotation rotation, qint64 timeStampNs);

    /**
     * @brief Gets the width without rotation applied.
     * @return The width without rotation applied.
     */
    int width() const;

    /**
     * @brief Gets the height without rotation applied.
     * @return The height without rotation applied.
     */
    int height() const;

    /**
     * @brief Gets the video rotation.
     * @return The video rotation.
     */
    RTCVideoRotation rotation() const;

    /**
     * @brief Gets the timestamp in nanoseconds.
     * @return The timestamp in nanoseconds.
     */
    qint64 timeStampNs() const;

    /**
     * @brief Gets the timestamp 90 kHz.
     * @return The timestamp 90 kHz.
     */
    int timeStamp() const;

    /**
     * @brief Sets the timestamp 90 kHz.
     * @param timeStamp The timestamp 90 kHz.
     */
    void setTimeStamp(int timeStamp);

    /**
     * @brief Gets the video frame buffer.
     * @return The video frame buffer.
     */
    std::shared_ptr<IRTCVideoFrameBuffer> buffer() const;

    /**
     * @brief Return a frame that is guaranteed to be I420, i.e. it is possible to access
     * the YUV data on it.
     * @return The I420 video frame.
     */
    std::shared_ptr<RTCVideoFrame> newI420VideoFrame();

  private:
    RTCVideoRotation rotation_;
    qint64 timeStampNs_;
    int timeStamp_;
    std::shared_ptr<IRTCVideoFrameBuffer> buffer_;
};
#endif // RTCVIDEOFRAME_H
