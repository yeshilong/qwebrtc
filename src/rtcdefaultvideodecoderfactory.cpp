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

#include "rtcdefaultvideodecoderfactory.h"

#include "rtcvideocodecconstants.h"
#include "rtcvideodecoderh264.h"
#include "rtcvideodecodervp8.h"
#include "rtcvideodecodervp9.h"

#if defined(RTC_DAV1D_IN_INTERNAL_DECODER_FACTORY)
#import "rtcvideodecoderav1.h"
#endif

RTCDefaultVideoDecoderFactory::RTCDefaultVideoDecoderFactory(QObject *parent)
    : IRTCVideoDecoderFactory{parent}
{
}

QVector<RTCVideoCodecInfo *> RTCDefaultVideoDecoderFactory::supportedCodecs()
{
    // QMap<QString, QString> constrainedHighParams;
    // constrainedHighParams["profile-level-id"] = kRTCMaxSupportedH264ProfileLevelConstrainedHigh;
    // constrainedHighParams["level-asymmetry-allowed"] = "1";
    // constrainedHighParams["packetization-mode"] = "1";
    // RTCVideoCodecInfo *constrainedHighInfo = new RTCVideoCodecInfo(
    //     RTCVideoCodecConstants::RTCVideoCodecH264Name(), constrainedHighParams);

    // QMap<QString, QString> constrainedBaselineParams;
    // constrainedBaselineParams["profile-level-id"] =
    //     kRTCMaxSupportedH264ProfileLevelConstrainedBaseline;
    // constrainedBaselineParams["level-asymmetry-allowed"] = "1";
    // constrainedBaselineParams["packetization-mode"] = "1";
    // RTCVideoCodecInfo *constrainedBaselineInfo = new RTCVideoCodecInfo(
    //     RTCVideoCodecConstants::RTCVideoCodecH264Name(), constrainedBaselineParams);

    RTCVideoCodecInfo *vp8Info =
        new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecVp8Name());

    QVector<RTCVideoCodecInfo *> result;
    // result << constrainedHighInfo;
    // result << constrainedBaselineInfo;
    result << vp8Info;

    if (RTCVideoDecoderVP9::isSupported())
    {
        RTCVideoCodecInfo *vp9Info =
            new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecVp9Name());
        result << vp9Info;
    }

#if defined(RTC_DAV1D_IN_INTERNAL_DECODER_FACTORY)
    RTCVideoCodecInfo *av1Info =
        new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecAv1Name());
    result << av1Info;
#endif

    return result;
}

IRTCVideoDecoder *RTCDefaultVideoDecoderFactory::createDecoder(RTCVideoCodecInfo *info)
{
    if (info->name() == RTCVideoCodecConstants::RTCVideoCodecH264Name())
    {
        return RTCVideoDecoderH264::h264Decoder();
    }
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecVp8Name())
    {
        return RTCVideoDecoderVP8::vp8Decoder();
    }
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecVp9Name() &&
             RTCVideoDecoderVP9::isSupported())
    {
        return RTCVideoDecoderVP9::vp9Decoder();
    }
#if defined(RTC_DAV1D_IN_INTERNAL_DECODER_FACTORY)
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecAv1Name())
    {
        return RTCVideoDecoderAV1::av1Decoder();
    }
#endif
    return nullptr;
}
