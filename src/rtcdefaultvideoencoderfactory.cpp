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

#include "rtcdefaultvideoencoderfactory.h"

#include "rtcvideocodecinfo_p.h"
#include "rtcvideocodecconstants.h"
#include "rtcvideoencoderh264.h"
#include "rtcvideoencodervp8.h"
#include "rtcvideoencodervp9.h"

#if defined(RTC_USE_LIBAOM_AV1_ENCODER)
#import "rtcvideoencoderav1.h"
#endif

namespace local
{
QVector<RTCVideoCodecInfo *> supportedCodecs()
{
    QMap<QString, QString> constrainedHighParams;

    // constrainedHighParams.insert("profile-level-id",
    //                              kRTCMaxSupportedH264ProfileLevelConstrainedHigh);
    // constrainedHighParams.insert("level-asymmetry-allowed", "1");
    // constrainedHighParams.insert("packetization-mode", "1");
    // RTCVideoCodecInfo *constrainedHighInfo(new RTCVideoCodecInfo(
    //     RTCVideoCodecConstants::RTCVideoCodecH264Name(), constrainedHighParams));

    // QMap<QString, QString> constrainedBaselineParams;
    // constrainedBaselineParams.insert("profile-level-id",
    //                                  kRTCMaxSupportedH264ProfileLevelConstrainedBaseline);
    // constrainedBaselineParams.insert("level-asymmetry-allowed", "1");
    // constrainedBaselineParams.insert("packetization-mode", "1");
    // RTCVideoCodecInfo *constrainedBaselineInfo(new RTCVideoCodecInfo(
    //     RTCVideoCodecConstants::RTCVideoCodecH264Name(), constrainedBaselineParams));

    RTCVideoCodecInfo *vp8Info(
        new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecVp8Name()));

    QVector<RTCVideoCodecInfo *> result;
    // result << constrainedHighInfo << constrainedBaselineInfo << vp8Info;
    result << vp8Info;

    if (RTCVideoEncoderVP9::isSupported())
    {
        QMap<QString, QString> vp9Params;
        RTCVideoCodecInfo *vp9Info(
            new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecVp9Name(), vp9Params,
                                  RTCVideoEncoderVP9::scalabilityModes()));
        result << vp9Info;
    }

#if defined(RTC_USE_LIBAOM_AV1_ENCODER)
    QMap<QString, QString> av1Params;
    RTCVideoCodecInfo *av1Info(new RTCVideoCodecInfo(RTCVideoCodecConstants::RTCVideoCodecAv1Name(),
                                                     av1Params,
                                                     RTCVideoEncoderAV1::scalabilityModes()));
    result << av1Info;
#endif

    return result;
}
} // namespace local

RTCDefaultVideoEncoderFactory::RTCDefaultVideoEncoderFactory(QObject *parent)
    : IRTCVideoEncoderFactory{parent}
{
    preferredCodec_ = nullptr;
}

RTCVideoCodecInfo *RTCDefaultVideoEncoderFactory::preferredCodec() const
{
    return preferredCodec_;
}

void RTCDefaultVideoEncoderFactory::setPreferredCodec(RTCVideoCodecInfo *codec)
{
    preferredCodec_ = codec;
}

IRTCVideoEncoder *RTCDefaultVideoEncoderFactory::createEncoder(RTCVideoCodecInfo *info)
{
    if (info->name() == RTCVideoCodecConstants::RTCVideoCodecH264Name())
    {
        return nullptr;
        // return new RTCVideoEncoderH264(info);
    }
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecVp8Name())
    {
        return RTCVideoEncoderVP8::vp8Encoder();
    }
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecVp9Name())
    {
        return RTCVideoEncoderVP9::vp9Encoder();
    }
#if defined(RTC_USE_LIBAOM_AV1_ENCODER)
    else if (info->name() == RTCVideoCodecConstants::RTCVideoCodecAv1Name())
    {
        return RTCVideoEncoderAV1::av1Encoder();
    }
#endif
    return nullptr;
}

QVector<RTCVideoCodecInfo *> RTCDefaultVideoEncoderFactory::supportedCodecs()
{
    QVector<RTCVideoCodecInfo *> _supportedCodecs = local::supportedCodecs();
    QVector<RTCVideoCodecInfo *> orderedCodecs;

    int index = _supportedCodecs.indexOf(preferredCodec_);
    if (index != -1)
    {
        orderedCodecs.append(_supportedCodecs.at(index));
        _supportedCodecs.removeAt(index);
    }
    orderedCodecs.append(_supportedCodecs);

    return orderedCodecs;
}
