#include "rtcdatachannelconfiguration.h"

RTCDataChannelConfiguration::RTCDataChannelConfiguration(QObject *parent) : QObject{parent}
{
}

bool RTCDataChannelConfiguration::isOrdered() const
{
    return isOrdered_;
}

void RTCDataChannelConfiguration::setIsOrdered(bool ordered)
{
    isOrdered_ = ordered;
}

int RTCDataChannelConfiguration::maxRetransmitTimeMs() const
{
    return maxRetransmitTimeMs_;
}

void RTCDataChannelConfiguration::setMaxRetransmitTimeMs(int time)
{
    maxRetransmitTimeMs_ = time;
}

int RTCDataChannelConfiguration::maxPacketLifeTime() const
{
    return maxPacketLifeTime_;
}

void RTCDataChannelConfiguration::setMaxPacketLifeTime(int time)
{
    maxPacketLifeTime_ = time;
}

int RTCDataChannelConfiguration::maxRetransmits() const
{
    return maxRetransmits_;
}

void RTCDataChannelConfiguration::setMaxRetransmits(int retransmits)
{
    maxRetransmits_ = retransmits;
}

bool RTCDataChannelConfiguration::isNegotiated() const
{
    return isNegotiated_;
}

void RTCDataChannelConfiguration::setIsNegotiated(bool negotiated)
{
    isNegotiated_ = negotiated;
}

int RTCDataChannelConfiguration::streamId() const
{
    return streamId_;
}

void RTCDataChannelConfiguration::setStreamId(int id)
{
    streamId_ = id;
}

int RTCDataChannelConfiguration::channelId() const
{
    return channelId_;
}

void RTCDataChannelConfiguration::setChannelId(int id)
{
    channelId_ = id;
}

QString RTCDataChannelConfiguration::protocol() const
{
    return protocol_;
}

void RTCDataChannelConfiguration::setProtocol(const QString &protocol)
{
    protocol_ = protocol;
}
