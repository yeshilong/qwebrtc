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

#include "rtcvideoencoderfactorysimulcast.h"

#include "rtcvideoencodersimulcast.h"

RTCVideoEncoderFactorySimulcast::RTCVideoEncoderFactorySimulcast(IRTCVideoEncoderFactory *primary,
                                                                 IRTCVideoEncoderFactory *fallback,
                                                                 QObject *parent)
    : IRTCVideoEncoderFactory{parent}
{
    primary_ = primary;
    fallback_ = fallback;
}

IRTCVideoEncoder *RTCVideoEncoderFactorySimulcast::createEncoder(RTCVideoCodecInfo *info)
{
    return RTCVideoEncoderSimulcast::simulcastEncoderWithPrimary(primary_, fallback_, info);
}

QVector<RTCVideoCodecInfo *> RTCVideoEncoderFactorySimulcast::supportedCodecs()
{
    QVector<RTCVideoCodecInfo *> codecs = primary_->supportedCodecs();
    QVector<RTCVideoCodecInfo *> fallbackCodecs = fallback_->supportedCodecs();
    for (RTCVideoCodecInfo *codec : fallbackCodecs)
    {
        if (!codecs.contains(codec))
        {
            codecs.append(codec);
        }
    }
    return codecs;
}
