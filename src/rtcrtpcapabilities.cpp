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

#include "rtcrtpcapabilities_p.h"

#include "rtcrtpcodeccapability.h"
#include "rtcrtpcodeccapability_p.h"

#include "rtc_base/checks.h"
#include "media/base/media_constants.h"

void RTCRtpCapabilitiesPrivate::init(const webrtc::RtpCapabilities &nativeRtpCapabilities)
{
    nativeRtpCapabilities_ = nativeRtpCapabilities;
}

RTCRtpCapabilitiesPrivate::RTCRtpCapabilitiesPrivate()
{
    init(webrtc::RtpCapabilities());
}

RTCRtpCapabilitiesPrivate::RTCRtpCapabilitiesPrivate(
    const webrtc::RtpCapabilities &nativeRtpCapabilities)
{
    init(nativeRtpCapabilities);
}

RTCRtpCapabilities::RTCRtpCapabilities(QObject *parent) : QObject{parent}
{
}

RTCRtpCapabilities::RTCRtpCapabilities(RTCRtpCapabilitiesPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QVector<RTCRtpCodecCapability *> RTCRtpCapabilities::codecs() const
{
    Q_D(const RTCRtpCapabilities);
    QVector<RTCRtpCodecCapability *> result;
    for (const webrtc::RtpCodecCapability &nativeCodecCapability : d->nativeRtpCapabilities_.codecs)
    {
        result.append(
            new RTCRtpCodecCapability(*new RTCRtpCodecCapabilityPrivate(nativeCodecCapability)));
    }
    return result;
}
