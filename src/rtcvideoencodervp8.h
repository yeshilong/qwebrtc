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

#ifndef RTCVIDEOENCODERVP8_H
#define RTCVIDEOENCODERVP8_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderVP8 class.
 */
class RTCVideoEncoderVP8 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderVP8 object.
     */
    explicit RTCVideoEncoderVP8(QObject *parent = nullptr);

    /**
     * @brief This returns a VP8 encoder that can be returned from a RTCVideoEncoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoEncoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the VP8 encoder.
     */
    static IRTCVideoEncoder *vp8Encoder();
};

#endif // RTCVIDEOENCODERVP8_H
