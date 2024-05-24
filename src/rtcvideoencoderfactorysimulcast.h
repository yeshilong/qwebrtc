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

#ifndef RTCVIDEOENCODERFACTORYSIMULCAST_H
#define RTCVIDEOENCODERFACTORYSIMULCAST_H

#include <QObject>

#include "rtcvideoencoderfactory.h"

/**
 * @brief The RTCVideoEncoderFactorySimulcast class.
 */
class RTCVideoEncoderFactorySimulcast : public IRTCVideoEncoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderFactorySimulcast object.
     * @param primary The primary encoder factory.
     * @param fallback The fallback encoder factory.
     */
    explicit RTCVideoEncoderFactorySimulcast(IRTCVideoEncoderFactory *primary,
                                             IRTCVideoEncoderFactory *fallback,
                                             QObject *parent = nullptr);

    /**
     * @brief Creates an encoder.
     * @param info The codec info.
     * @return The created encoder.
     */
    IRTCVideoEncoder *createEncoder(RTCVideoCodecInfo *info);

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    QVector<RTCVideoCodecInfo *> supportedCodecs();

    /**
     * @brief Gets the implementations.
     * @return The implementations.
     */
    QVector<RTCVideoCodecInfo *> implementations() = 0;

    /**
     * @brief Gets the encoder selector.
     * @return The encoder selector.
     */
    IRTCVideoEncoderSelector *encoderSelector() = 0;

  private:
    IRTCVideoEncoderFactory *primary_;
    IRTCVideoEncoderFactory *fallback_;
};

#endif // RTCVIDEOENCODERFACTORYSIMULCAST_H
