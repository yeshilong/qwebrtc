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

#ifndef RTCRTPENCODINGPARAMETERS_P_H
#define RTCRTPENCODINGPARAMETERS_P_H

#include <QString>
#include <QVariant>

#include "api/rtp_parameters.h"

#include "rtctypes.h"

class RTCRtpEncodingParametersPrivate
{
  public:
    RTCRtpEncodingParametersPrivate();
    RTCRtpEncodingParametersPrivate(
        const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters);
    void init(const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters);

    webrtc::RtpEncodingParameters nativeRtpEncodingParameters() const;

    QString rid_;
    bool isActive_;
    QVariant maxBitrateBps_;
    QVariant minBitrateBps_;
    QVariant maxFramerate_;
    QVariant numTemporalLayers_;
    QVariant scaleResolutionDownBy_;
    QVariant ssrc_;
    double bitratePriority_;
    RTCPriority networkPriority_;
    bool adaptiveAudioPacketTime_;
    QString scalabilityMode_;
};

#endif // RTCRTPENCODINGPARAMETERS_P_H
