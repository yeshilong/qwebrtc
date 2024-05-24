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

#include "rtcrtpreceiver.h"
#include "rtcrtpparameters_p.h"
#include "rtcrtpreceiver_p.h"

#include "rtcmediastreamtrack_p.h"
#include "rtcrtcpparameters_p.h"

#include <memory>

#include "api/media_stream_interface.h"

namespace webrtc
{

RtpReceiverDelegateAdapter::RtpReceiverDelegateAdapter(std::shared_ptr<RTCRtpReceiver> receiver)
{
    RTC_CHECK(receiver);
    receiver_ = receiver;
}

void RtpReceiverDelegateAdapter::OnFirstPacketReceived(cricket::MediaType media_type)
{
    auto receiver = receiver_.lock();
    if (receiver)
    {
        Q_EMIT receiver->rtpReceiverDidReceiveFirstPacketForMediaType(
            static_cast<RTCRtpMediaType>(media_type));
    }
}

} // namespace webrtc

RTCRtpReceiverPrivate::RTCRtpReceiverPrivate(
    RTCPeerConnectionFactory *factory, rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver)
{
    Q_ASSERT(factory_);
    Q_ASSERT(receiver);
    factory_ = factory;
    nativeRtpReceiver_ = receiver;

    auto q = std::make_shared<RTCRtpReceiver>();
    q->d_ptr = this;
    observer_.reset(new webrtc::RtpReceiverDelegateAdapter(q));
    nativeRtpReceiver_->SetObserver(observer_.get());
}

rtc::scoped_refptr<webrtc::RtpReceiverInterface> RTCRtpReceiverPrivate::nativeRtpReceiver() const
{
    return nativeRtpReceiver_;
}

void RTCRtpReceiverPrivate::setFrameDecryptor(
    const rtc::scoped_refptr<webrtc::FrameDecryptorInterface> frameDecryptor)
{
    nativeRtpReceiver_->SetFrameDecryptor(frameDecryptor);
}

RTCRtpReceiver::RTCRtpReceiver(QObject *parent) : QObject{parent}, d_ptr{nullptr}
{
}

RTCRtpReceiver::RTCRtpReceiver(RTCRtpReceiverPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCRtpReceiver::receiverId() const
{
    return QString::fromStdString(d_ptr->nativeRtpReceiver()->id());
}

RTCRtpParameters *RTCRtpReceiver::parameters() const
{
    return new RTCRtpParameters(
        *new RTCRtpParametersPrivate(d_ptr->nativeRtpReceiver()->GetParameters()));
}
