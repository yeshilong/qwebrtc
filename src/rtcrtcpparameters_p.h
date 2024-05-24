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

#ifndef RTCRTCPPARAMETERS_P_H
#define RTCRTCPPARAMETERS_P_H

#include <QObject>

#include "api/rtp_parameters.h"

#include "rtcrtcpparameters.h"

class RTCRtcpParametersPrivate
{
  public:
    explicit RTCRtcpParametersPrivate();
    RTCRtcpParametersPrivate(const webrtc::RtcpParameters &nativeRtcpParameters);
    void init(const webrtc::RtcpParameters &nativeRtcpParameters);
    webrtc::RtcpParameters nativeRtcpParameters() const;

    QString cName_;
    bool isReducedSize_;
};

#endif // RTCRTCPPARAMETERS_P_H
