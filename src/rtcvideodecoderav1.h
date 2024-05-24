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

#ifndef RTCVIDEODECODERAV1_H
#define RTCVIDEODECODERAV1_H

#include <QObject>
#include <QVector>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderAV1 class represents an AV1 video decoder.
 *
 * This class implements the RTCVideoDecoder interface and can be used with a
 * RTCVideoDecoderFactory injected into RTCPeerConnectionFactory.
 */
class RTCVideoDecoderAV1 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Creates an instance of the AV1 video decoder.
     * @return A pointer to the AV1 video decoder.
     *
     * This method returns an AV1 decoder that can be used with a
     * RTCVideoDecoderFactory injected into RTCPeerConnectionFactory.
     */
    explicit RTCVideoDecoderAV1(QObject *parent = nullptr);

    /**
     * @brief Gets the AV1 decoder.
     * @return The AV1 decoder.
     */
    static IRTCVideoDecoder *av1Decoder();
};

#endif // RTCVIDEODECODERAV1_H
