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
