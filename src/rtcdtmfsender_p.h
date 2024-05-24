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

#ifndef RTCDTMFSENDER_P_H
#define RTCDTMFSENDER_P_H

#include "rtcdtmfsender.h"

#include "api/dtmf_sender_interface.h"

class RTCDtmfSenderPrivate
{
  public:
    explicit RTCDtmfSenderPrivate(rtc::scoped_refptr<webrtc::DtmfSenderInterface> dtmfSender);
    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender() const;

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender_;
};

#endif // RTCDTMFSENDER_P_H
