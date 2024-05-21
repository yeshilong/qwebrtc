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

#include "rtcvideoencoderfactoryh264.h"

#include "rtcvideocodecconstants.h"
#include "rtch264profilelevelid.h"
#include "rtcvideoencoderh264.h"

RTCVideoEncoderFactoryH264::RTCVideoEncoderFactoryH264(QObject *parent)
    : IRTCVideoEncoderFactory{parent}
{
}

QVector<RTCVideoCodecInfo *> RTCVideoEncoderFactoryH264::supportedCodecs()
{
    QVector<RTCVideoCodecInfo *> codecs;
    QString codecName = RTCVideoCodecConstants::RTCVideoCodecH264Name();

    QMap<QString, QString> constrainedHighParams = {
        {"profile-level-id",
         RTCH264ProfileLevelId::RTCMaxSupportedH264ProfileLevelConstrainedHigh()},
        {"level-asymmetry-allowed", "1"},
        {"packetization-mode", "1"}};
    RTCVideoCodecInfo constrainedHighInfo(codecName, constrainedHighParams);
    codecs.append(&constrainedHighInfo);

    QMap<QString, QString> constrainedBaselineParams = {
        {"profile-level-id",
         RTCH264ProfileLevelId::RTCMaxSupportedH264ProfileLevelConstrainedBaseline()},
        {"level-asymmetry-allowed", "1"},
        {"packetization-mode", "1"}};
    RTCVideoCodecInfo constrainedBaselineInfo(codecName, constrainedBaselineParams);
    codecs.append(&constrainedBaselineInfo);

    return codecs;
}

IRTCVideoEncoder *RTCVideoEncoderFactoryH264::createEncoder(RTCVideoCodecInfo *info)
{
    return RTCVideoEncoderH264::h264Encoder(info);
}