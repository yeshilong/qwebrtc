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

#ifndef RTCRTPTRANSCEIVER_P_H
#define RTCRTPTRANSCEIVER_P_H

#include <QString>

#include "rtcrtptransceiver.h"

#include "api/rtp_transceiver_interface.h"

class RTCPeerConnectionFactory;
class RTCRtpTransceiverPrivate
{
  public:
    explicit RTCRtpTransceiverPrivate(
        RTCPeerConnectionFactory *factory,
        rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver);
    ~RTCRtpTransceiverPrivate();
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver() const;

    RTCPeerConnectionFactory *factory_;
    IRTCRtpSender *sender_;
    RTCRtpReceiver *receiver_;
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver_;
};

#endif // RTCRTPTRANSCEIVER_P_H
