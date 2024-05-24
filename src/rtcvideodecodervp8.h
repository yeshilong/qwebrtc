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

#ifndef RTCVIDEODECODERVP8_H
#define RTCVIDEODECODERVP8_H

#include <QObject>

#include "rtcvideodecoder.h"

class RTCVideoDecoderVP8 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderVP8 object.
     */
    explicit RTCVideoDecoderVP8(QObject *parent = nullptr);

    /**
     * @brief Gets the VP8 decoder.
     * @return This returns a VP8 decoder that can be returned from a RTCVideoDecoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoDecoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     */
    static IRTCVideoDecoder *vp8Decoder();
};

#endif // RTCVIDEODECODERVP8_H
