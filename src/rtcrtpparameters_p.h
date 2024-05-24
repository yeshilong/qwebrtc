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

#ifndef RTCRTPPARAMETERS_P_H
#define RTCRTPPARAMETERS_P_H

#include <QString>
#include <QVector>
#include <QVariant>

#include "api/rtp_parameters.h"

#include "rtcrtcpparameters.h"
#include "rtcrtcpparameters.h"
#include "rtcrtpheaderextension.h"
#include "rtcrtpencodingparameters.h"
#include "rtcrtpcodecparameters.h"

class RTCRtpParametersPrivate
{
  public:
    RTCRtpParametersPrivate();
    RTCRtpParametersPrivate(const webrtc::RtpParameters &nativeRtpParameters);
    void init(const webrtc::RtpParameters &nativeRtpParameters);
    webrtc::RtpParameters nativeRtpParameters() const;

    QString transactionId_;
    RTCRtcpParameters *rtcp_;
    QVector<RTCRtpHeaderExtension *> headerExtensions_;
    QVector<RTCRtpEncodingParameters *> encodings_;
    QVector<RTCRtpCodecParameters *> codecs_;
    QVariant degradationPreference_;
};

#endif // RTCRTPPARAMETERS_P_H
