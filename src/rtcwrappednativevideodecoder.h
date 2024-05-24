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

#ifndef RTCWRAPPEDNATIVEVIDEODECODER_H
#define RTCWRAPPEDNATIVEVIDEODECODER_H

#include <QObject>

#include "rtcvideodecoder.h"

#include "media/base/codec.h"
#include "api/video_codecs/video_decoder.h"

/**
 * @brief The RTCWrappedNativeVideoDecoder class.
 */
class RTCWrappedNativeVideoDecoder : public IRTCVideoDecoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCWrappedNativeVideoDecoder object.
     */
    explicit RTCWrappedNativeVideoDecoder(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCWrappedNativeVideoDecoder object.
     * @param decoder The decoder.
     */
    explicit RTCWrappedNativeVideoDecoder(std::unique_ptr<webrtc::VideoDecoder> decoder,
                                          QObject *parent = nullptr);

    /**
     * @brief This moves the ownership of the decoder to the caller.
     * @return The decoder.
     */
    std::unique_ptr<webrtc::VideoDecoder> releaseWrappedDecoder();

    /**
     * @brief Sets the callback.
     * @param callback The callback.
     */
    void setCallback(RTCVideoDecoderCallback callback);

    /**
     * @brief Starts decode with number of cores.
     * @param numberOfCores The number of cores.
     * @return The result.
     */
    int startDecodeWithNumberOfCores(int numberOfCores);

    /**
     * @brief Releases the decoder.
     * @return The result.
     */
    int releaseDecoder();

    /**
     * @brief Decodes the encoded image.
     * @param encodedImage The encoded image.
     * @param missingFrames The missing frames.
     * @param info The codec specific info.
     * @param renderTimeMs The render time in milliseconds.
     * @return The result.
     */
    int decode(std::shared_ptr<RTCEncodedImage> encodedImage, bool missingFrames,
               std::shared_ptr<IRTCCodecSpecificInfo> info, qint64 renderTimeMs);

    /**
     * @brief Gets the implementation name.
     * @return The implementation name.
     */
    QString implementationName() const;

  private:
    std::unique_ptr<webrtc::VideoDecoder> wrappedDecoder_;
};

#endif // RTCWRAPPEDNATIVEVIDEODECODER_H
