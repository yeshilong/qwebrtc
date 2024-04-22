#include "rtcdatachannel.h"

RTCDataChannel::RTCDataChannel(QObject *parent) : QObject{parent}
{
}

QString RTCDataChannel::label() const
{
    return label_;
}

bool RTCDataChannel::isReliable() const
{
    return isReliable_;
}

bool RTCDataChannel::isOrdered() const
{
    return isOrdered_;
}

unsigned int RTCDataChannel::maxRetransmitTime() const
{
    return maxPacketLifeTime_;
}

unsigned short RTCDataChannel::maxPacketLifeTime() const
{
    return maxPacketLifeTime_;
}

unsigned short RTCDataChannel::maxRetransmits() const
{
    return maxRetransmits_;
}

QString RTCDataChannel::protocol() const
{
    return protocol_;
}

bool RTCDataChannel::isNegotiated() const
{
    return isNegotiated_;
}

int RTCDataChannel::streamId() const
{
    return streamId_;
}

int RTCDataChannel::channelId() const
{
    return channelId_;
}

RTCDataChannelState RTCDataChannel::readyState() const
{
    return readyState_;
}

unsigned long long RTCDataChannel::bufferedAmount() const
{
    return bufferedAmount_;
}

void RTCDataChannel::close()
{
}

bool RTCDataChannel::sendData(const QByteArray &data)
{
    return false;
}
