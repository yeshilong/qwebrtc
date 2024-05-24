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

#ifndef RTCRTPRECEIVER_P_H
#define RTCRTPRECEIVER_P_H

#include "api/scoped_refptr.h"
#include "api/rtp_receiver_interface.h"
#include "api/crypto/frame_decryptor_interface.h"

#include "rtcrtpreceiver.h"

namespace webrtc
{

class RtpReceiverDelegateAdapter : public RtpReceiverObserverInterface
{
  public:
    RtpReceiverDelegateAdapter(std::shared_ptr<RTCRtpReceiver> receiver);

    void OnFirstPacketReceived(cricket::MediaType media_type) override;

  private:
    std::weak_ptr<RTCRtpReceiver> receiver_;
};

} // namespace webrtc

class RTCPeerConnectionFactory;
class RTCRtpReceiverPrivate
{
  public:
    RTCRtpReceiverPrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver);
    rtc::scoped_refptr<webrtc::RtpReceiverInterface> nativeRtpReceiver() const;
    void setFrameDecryptor(
        const rtc::scoped_refptr<webrtc::FrameDecryptorInterface> frameDecryptor);

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::RtpReceiverInterface> nativeRtpReceiver_;
    std::unique_ptr<webrtc::RtpReceiverDelegateAdapter> observer_;
};

#endif // RTCRTPRECEIVER_P_H
