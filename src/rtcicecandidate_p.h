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

#ifndef RTCICECANDIDATE_P_H
#define RTCICECANDIDATE_P_H

#include <QString>

#include "qwebrtcglobal.h"

#include "rtcicecandidate.h"

#include "api/jsep.h"

class QWEBRTC_EXPORT RTCIceCandidatePrivate
{
  public:
    RTCIceCandidatePrivate(const QString &sdp, int sdpMLineIndex, const QString &sdpMid);
    RTCIceCandidatePrivate(const webrtc::IceCandidateInterface *candidate);
    std::unique_ptr<webrtc::IceCandidateInterface> nativeIceCandidate() const;

    QString sdpMid_;
    int sdpMLineIndex_;
    QString sdp_;
    QString serverUrl_;
};

#endif // RTCICECANDIDATE_P_H
