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

#ifndef RTCVIDEOENCODERH264_H
#define RTCVIDEOENCODERH264_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderH264 class.
 */
class RTCVideoEncoderH264 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderH264 object.
     * @param codecInfo The codec info.
     */
    explicit RTCVideoEncoderH264(QObject *parent = nullptr);

    /**
     * @brief This returns a H264 encoder that can be returned from a RTCVideoEncoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoEncoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the H264 encoder.
     */
    static IRTCVideoEncoder *h264Encoder(RTCVideoCodecInfo *codecInfo);

    /**
     * @brief Checks if the H264 encoder is supported.
     * @return True if the H264 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Gets the scalability modes.
     * @return The scalability modes.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERH264_H
