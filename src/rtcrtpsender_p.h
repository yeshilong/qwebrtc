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

#ifndef RTCRTPSENDER_P_H
#define RTCRTPSENDER_P_H

#include <QString>

#include "api/scoped_refptr.h"
#include "api/rtp_sender_interface.h"
#include "api/crypto/frame_encryptor_interface.h"

class RTCPeerConnectionFactory;
class IRTCDtmfSender;
class RTCRtpSenderPrivate
{
  public:
    RTCRtpSenderPrivate(RTCPeerConnectionFactory *factory,
                        const rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender);
    rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender() const;
    rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frameEncryptor() const;
    void setFrameEncryptor(
        const rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frameEncryptor);

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender_;
    IRTCDtmfSender *dtmfSender_;
};

#endif // RTCRTPSENDER_P_H
