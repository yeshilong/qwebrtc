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

#ifndef RTCVIDEODECODERH264_H
#define RTCVIDEODECODERH264_H

#include <QObject>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderH264 class.
 */
class RTCVideoDecoderH264 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderH264 object.
     */
    explicit RTCVideoDecoderH264(QObject *parent = nullptr);

    /**
     * @brief This returns a H264 decoder that can be returned from a RTCVideoDecoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoDecoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the H264 decoder.
     */
    static IRTCVideoDecoder *h264Decoder();

    /**
     * @brief Checks if the H264 decoder is supported.
     * @return True if the H264 decoder is supported, false otherwise.
     */
    static bool isSupported();
};

#endif // RTCVIDEODECODERH264_H
