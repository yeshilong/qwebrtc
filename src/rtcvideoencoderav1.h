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

#ifndef RTCVIDEOENCODERAV1_H
#define RTCVIDEOENCODERAV1_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderAV1 class.
 */
class RTCVideoEncoderAV1 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief This returns a AV1 encoder that can be returned from a RTCVideoEncoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoEncoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the AV1 encoder.
     */
    explicit RTCVideoEncoderAV1(QObject *parent = nullptr);

    /**
     * @brief Checks if the AV1 encoder is supported.
     * @return True if the AV1 encoder is supported, false otherwise.
     */
    static IRTCVideoEncoder *av1Encoder();

    /**
     * @brief Checks if the AV1 encoder is supported.
     * @return True if the AV1 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Returns the scalability modes for the AV1 encoder.
     * @return A list of scalability modes as strings.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERAV1_H
