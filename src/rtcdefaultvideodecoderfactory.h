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

#ifndef RTCDEFAULTVIDEODECODERFACTORY_H
#define RTCDEFAULTVIDEODECODERFACTORY_H

#include <QObject>

#include "rtcvideodecoderfactory.h"

/**
 * @brief The RTCDefaultVideoDecoderFactory class.
 */
class RTCDefaultVideoDecoderFactory : public IRTCVideoDecoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCDefaultVideoDecoderFactory object.
     */
    explicit RTCDefaultVideoDecoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates a decoder.
     * @param info The codec info.
     * @return The decoder.
     */
    IRTCVideoDecoder *createDecoder(RTCVideoCodecInfo *info);

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    QVector<RTCVideoCodecInfo *> supportedCodecs();
};

#endif // RTCDEFAULTVIDEODECODERFACTORY_H
