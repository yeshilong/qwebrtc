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
    DataChannelDelegateAdapter(RTCDataChannel *channel) : channel_(std::move(channel))
    {
    }

    void OnStateChange() override
    {
        Q_EMIT channel_->dataChannelDidChangeState();
    }

    void OnMessage(const DataBuffer &buffer) override
    {
        auto dataBuffer = new RTCDataBufferPrivate(buffer);
        Q_EMIT channel_->dataChannelDidReceiveMessageWithBuffer(dataBuffer->data());
    }

    void OnBufferedAmountChange(uint64_t previousAmount) override
    {
        Q_EMIT channel_->dataChannelDidChangeBufferedAmount(previousAmount);
    }

  private:
    std::unique_ptr<RTCDataChannel> channel_;
};
}

class RTCDataChannelPrivate
{
  public:
    explicit RTCDataChannelPrivate(
        RTCPeerConnectionFactory *factory,
        rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel);
    ~RTCDataChannelPrivate();

    QString label() const;
    bool isReliable() const;
    bool isOrdered() const;
    unsigned int maxRetransmitTime() const;
    unsigned short maxPacketLifeTime() const;
    unsigned short maxRetransmits() const;
    QString protocol() const;
    bool isNegotiated() const;
    int streamId() const;
    int channelId() const;
    RTCDataChannelState readyState() const;
    unsigned long long bufferedAmount() const;

    void close();
    bool sendData(const webrtc::DataBuffer *data);

    std::unique_ptr<RTCDataChannel> q_ptr;

  private:
    unsigned short maxPacketLifeTime_;
    int channelId_;

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel_;
    std::unique_ptr<webrtc::DataChannelDelegateAdapter> observer_;
    bool _isObserverRegistered;
};

#endif // RTCDATACHANNEL_P_H
