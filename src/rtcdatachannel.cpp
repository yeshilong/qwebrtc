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
    Q_D(const RTCDataChannel);
    return d->label();
}

bool RTCDataChannel::isReliable() const
{
    Q_D(const RTCDataChannel);
    return d->isReliable();
}

bool RTCDataChannel::isOrdered() const
{
    Q_D(const RTCDataChannel);
    return d->isOrdered();
}

unsigned int RTCDataChannel::maxRetransmitTime() const
{
    Q_D(const RTCDataChannel);
    return d->maxRetransmitTime();
}

unsigned short RTCDataChannel::maxPacketLifeTime() const
{
    Q_D(const RTCDataChannel);
    return d->maxPacketLifeTime();
}

unsigned short RTCDataChannel::maxRetransmits() const
{
    Q_D(const RTCDataChannel);
    return d->maxRetransmits();
}

QString RTCDataChannel::protocol() const
{
    Q_D(const RTCDataChannel);
    return d->protocol();
}

bool RTCDataChannel::isNegotiated() const
{
    Q_D(const RTCDataChannel);
    return d->isNegotiated();
}

int RTCDataChannel::streamId() const
{
    Q_D(const RTCDataChannel);
    return d->streamId();
}

int RTCDataChannel::channelId() const
{
    Q_D(const RTCDataChannel);
    return d->channelId();
}

RTCDataChannelState RTCDataChannel::readyState() const
{
    Q_D(const RTCDataChannel);
    return d->readyState();
}

unsigned long long RTCDataChannel::bufferedAmount() const
{
    Q_D(const RTCDataChannel);
    return d->bufferedAmount();
}

void RTCDataChannel::close()
{
    Q_D(RTCDataChannel);
    d->close();
}

bool RTCDataChannel::sendData(const RTCDataBuffer *data)
{
    Q_D(RTCDataChannel);
    return d->sendData(data->d_ptr->nativeDataBuffer());
}
