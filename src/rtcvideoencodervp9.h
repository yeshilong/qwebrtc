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

#ifndef RTCVIDEOENCODERVP9_H
#define RTCVIDEOENCODERVP9_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderVP9 class.
 */
class RTCVideoEncoderVP9 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderVP9 object.
     */
    explicit RTCVideoEncoderVP9(QObject *parent = nullptr);

    /**
     * @brief This returns a VP9 encoder that can be returned from a RTCVideoEncoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoEncoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the VP9 encoder.
     */
    static IRTCVideoEncoder *vp9Encoder();

    /**
     * @brief Checks if the VP9 encoder is supported.
     * @return True if the VP9 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Gets the scalability modes.
     * @return The scalability modes.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERVP9_H
