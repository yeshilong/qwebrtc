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

#ifndef RTCDATACHANNEL_P_H
#define RTCDATACHANNEL_P_H

#include "rtcdatachannel.h"
#include "rtcdatabuffer_p.h"

#include "api/scoped_refptr.h"
#include "api/data_channel_interface.h"

#include <QByteArray>

#include <memory>

class RTCPeerConnectionFactory;

namespace webrtc
{

class DataChannelDelegateAdapter : public DataChannelObserver
{
  public:
    DataChannelDelegateAdapter(std::shared_ptr<RTCDataChannel> channel);

    void OnStateChange() override;
    void OnMessage(const DataBuffer &buffer) override;
    void OnBufferedAmountChange(uint64_t previousAmount) override;

  private:
    std::weak_ptr<RTCDataChannel> channel_;
};
} // namespace webrtc

class RTCDataChannelPrivate
{
  public:
    explicit RTCDataChannelPrivate(
        RTCPeerConnectionFactory *factory,
        rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel);
    ~RTCDataChannelPrivate();

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel_;
    std::unique_ptr<webrtc::DataChannelDelegateAdapter> observer_;
    bool _isObserverRegistered;
    RTCDataChannel *q_ptr;

    unsigned short maxPacketLifeTime_;
    int channelId_;
};

#endif // RTCDATACHANNEL_P_H
