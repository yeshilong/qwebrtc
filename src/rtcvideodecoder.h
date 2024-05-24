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

#ifndef RTCVIDEODECODER_H
#define RTCVIDEODECODER_H

#include <QObject>
#include <QString>

#include <functional>

class RTCVideoFrame;
class RTCEncodedImage;
class IRTCCodecSpecificInfo;

/**
 * @brief The RTCVideoDecoderCallback function pointer.
 */
using RTCVideoDecoderCallback = std::function<void(std::shared_ptr<RTCVideoFrame> frame)>;

/**
 * @brief The IRTCVideoDecoder class.
 */
class IRTCVideoDecoder : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoDecoder object.
     */
    explicit IRTCVideoDecoder(QObject *parent = nullptr);

    /**
     * @brief Sets the callback.
     * @param callback The callback.
     */
    virtual void setCallback(RTCVideoDecoderCallback callback) = 0;

    /**
     * @brief Starts decode with number of cores.
     * @param numberOfCores The number of cores.
     * @return The result.
     */
    virtual int startDecodeWithNumberOfCores(int numberOfCores) = 0;

    /**
     * @brief Releases the decoder.
     * @return The result.
     */
    virtual int releaseDecoder() = 0;

    /**
     * @brief Decodes the encoded image.
     * @param encodedImage The encoded image.
     * @param missingFrames The missing frames.
     * @param info The codec specific info.
     * @param renderTimeMs The render time in milliseconds.
     * @return The result.
     */
    virtual int decode(std::shared_ptr<RTCEncodedImage> encodedImage, bool missingFrames,
                       std::shared_ptr<IRTCCodecSpecificInfo> info, qint64 renderTimeMs) = 0;

    /**
     * @brief Gets the implementation name.
     * @return The implementation name.
     */
    virtual QString implementationName() const = 0;
};

#endif // RTCVIDEODECODER_H
