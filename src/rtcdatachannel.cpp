#include "rtcdatachannel.h"
#include "rtcdatachannel_p.h"

namespace webrtc
{

DataChannelDelegateAdapter::DataChannelDelegateAdapter(std::shared_ptr<RTCDataChannel> channel)
{
    channel_ = channel;
}

void DataChannelDelegateAdapter::OnStateChange()
{
    auto channel = channel_.lock();
    if (channel)
    {

        Q_EMIT channel->dataChannelDidChangeState();
    }
}

void DataChannelDelegateAdapter::OnMessage(const DataBuffer &buffer)
{
    auto channel = channel_.lock();
    if (channel)
    {
        auto dataBuffer = new RTCDataBufferPrivate(buffer);
        auto bytes =
            QByteArray(reinterpret_cast<const char *>(dataBuffer->nativeDataBuffer_->data.data()),
                       dataBuffer->nativeDataBuffer_->data.size());
        Q_EMIT channel->dataChannelDidReceiveMessageWithBuffer(bytes);
        delete dataBuffer;
    }
}

void DataChannelDelegateAdapter::OnBufferedAmountChange(uint64_t previousAmount)
{
    auto channel = channel_.lock();
    if (channel)
    {
        Q_EMIT channel->dataChannelDidChangeBufferedAmount(previousAmount);
    }
}

} // namespace webrtc

RTCDataChannelPrivate::RTCDataChannelPrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeDataChannel);

    factory_ = factory;
    nativeDataChannel_ = nativeDataChannel;

    auto q = std::make_shared<RTCDataChannel>();
    q->d_ptr = this;
    observer_.reset(new webrtc::DataChannelDelegateAdapter(q));
}

RTCDataChannelPrivate::~RTCDataChannelPrivate()
{
    nativeDataChannel_->UnregisterObserver();
}

QString RTCDataChannel::label() const
{
    Q_D(const RTCDataChannel);
    return QString::fromStdString(d_ptr->nativeDataChannel_->label());
}

bool RTCDataChannel::isReliable() const
{
    Q_D(const RTCDataChannel);
    return d_ptr->nativeDataChannel_->reliable();
}

bool RTCDataChannel::isOrdered() const
{
    return d_ptr->nativeDataChannel_->ordered();
}

unsigned int RTCDataChannel::maxRetransmitTime() const
{
    return d_ptr->maxPacketLifeTime_;
}

unsigned short RTCDataChannel::maxPacketLifeTime() const
{
    return d_ptr->nativeDataChannel_->maxRetransmitTime();
}

unsigned short RTCDataChannel::maxRetransmits() const
{
    return d_ptr->nativeDataChannel_->maxRetransmits();
}

QString RTCDataChannel::protocol() const
{
    return QString::fromStdString(d_ptr->nativeDataChannel_->protocol());
}

bool RTCDataChannel::isNegotiated() const
{
    return d_ptr->nativeDataChannel_->negotiated();
}

int RTCDataChannel::streamId() const
{
    return d_ptr->channelId_;
}

int RTCDataChannel::channelId() const
{
    return d_ptr->nativeDataChannel_->id();
}

RTCDataChannelState RTCDataChannel::readyState() const
{
    return static_cast<RTCDataChannelState>(d_ptr->nativeDataChannel_->state());
}

unsigned long long RTCDataChannel::bufferedAmount() const
{
    return d_ptr->nativeDataChannel_->buffered_amount();
}

void RTCDataChannel::close()
{
    d_ptr->nativeDataChannel_->Close();
}

bool RTCDataChannel::sendData(const RTCDataBuffer *data)
{
    Q_D(RTCDataChannel);
    return d_ptr->nativeDataChannel_->Send(*data->d_ptr->nativeDataBuffer());
}

RTCDataChannel::~RTCDataChannel()
{
    delete d_ptr;
}
