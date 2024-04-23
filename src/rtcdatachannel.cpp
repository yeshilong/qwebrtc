#include "rtcdatachannel.h"
#include "rtcdatachannel_p.h"

RTCDataChannelPrivate::RTCDataChannelPrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::DataChannelInterface> nativeDataChannel)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeDataChannel);

    factory_ = factory;
    nativeDataChannel_ = nativeDataChannel;
    observer_.reset(new webrtc::DataChannelDelegateAdapter(this->q_ptr.get()));
}

RTCDataChannelPrivate::~RTCDataChannelPrivate()
{
    nativeDataChannel_->UnregisterObserver();
}

QString RTCDataChannelPrivate::label() const
{
    return QString::fromStdString(nativeDataChannel_->label());
}

bool RTCDataChannelPrivate::isReliable() const
{
    return nativeDataChannel_->reliable();
}

bool RTCDataChannelPrivate::isOrdered() const
{
    return nativeDataChannel_->ordered();
}

unsigned int RTCDataChannelPrivate::maxRetransmitTime() const
{
    return maxPacketLifeTime_;
}

unsigned short RTCDataChannelPrivate::maxPacketLifeTime() const
{
    return nativeDataChannel_->maxRetransmitTime();
}

unsigned short RTCDataChannelPrivate::maxRetransmits() const
{
    return nativeDataChannel_->maxRetransmits();
}

QString RTCDataChannelPrivate::protocol() const
{
    return QString::fromStdString(nativeDataChannel_->protocol());
}

bool RTCDataChannelPrivate::isNegotiated() const
{
    return nativeDataChannel_->negotiated();
}

int RTCDataChannelPrivate::streamId() const
{
    return channelId_;
}

int RTCDataChannelPrivate::channelId() const
{
    return nativeDataChannel_->id();
}

RTCDataChannelState RTCDataChannelPrivate::readyState() const
{
    return static_cast<RTCDataChannelState>(nativeDataChannel_->state());
}

unsigned long long RTCDataChannelPrivate::bufferedAmount() const
{
    return nativeDataChannel_->buffered_amount();
}

void RTCDataChannelPrivate::close()
{
    nativeDataChannel_->Close();
}

bool RTCDataChannelPrivate::sendData(const webrtc::DataBuffer *data)
{
    return nativeDataChannel_->Send(*data);
}

RTCDataChannel::~RTCDataChannel()
{
    delete d_ptr;
}

QString RTCDataChannel::label() const
{
    return d_ptr->label();
}

bool RTCDataChannel::isReliable() const
{
    return d_ptr->isReliable();
}

bool RTCDataChannel::isOrdered() const
{
    return d_ptr->isOrdered();
}

unsigned int RTCDataChannel::maxRetransmitTime() const
{
    return d_ptr->maxRetransmitTime();
}

unsigned short RTCDataChannel::maxPacketLifeTime() const
{
    return d_ptr->maxPacketLifeTime();
}

unsigned short RTCDataChannel::maxRetransmits() const
{
    return d_ptr->maxRetransmits();
}

QString RTCDataChannel::protocol() const
{
    return d_ptr->protocol();
}

bool RTCDataChannel::isNegotiated() const
{
    return d_ptr->isNegotiated();
}

int RTCDataChannel::streamId() const
{
    return d_ptr->streamId();
}

int RTCDataChannel::channelId() const
{
    return d_ptr->channelId();
}

RTCDataChannelState RTCDataChannel::readyState() const
{
    return d_ptr->readyState();
}

unsigned long long RTCDataChannel::bufferedAmount() const
{
    return d_ptr->bufferedAmount();
}

void RTCDataChannel::close()
{
    d_ptr->close();
}

bool RTCDataChannel::sendData(const RTCDataBuffer *data)
{
    return d_ptr->sendData(data->d_ptr->nativeDataBuffer());
}
