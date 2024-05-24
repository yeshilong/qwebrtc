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

#ifndef RTCVIDEOENCODERH264MF_H
#define RTCVIDEOENCODERH264MF_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderH264MF class.
 */
class RTCVideoEncoderH264MF : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderH264MF object.
     */
    explicit RTCVideoEncoderH264MF(QObject *parent = nullptr);

    /**
     * @brief Gets a H264 MF encoder.
     * @return The H264 MF encoder.
     */
    static IRTCVideoEncoder *h264MFEncoder();

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    static QVector<RTCVideoCodecInfo *> supportedCodecs();
};

#endif // RTCVIDEOENCODERH264MF_H
