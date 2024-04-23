#include "rtcdatachannelconfiguration.h"
#include "rtcdatachannelconfiguration_p.h"

RTCDataChannelConfigurationPrivate::RTCDataChannelConfigurationPrivate()
{
}

webrtc::DataChannelInit RTCDataChannelConfigurationPrivate::nativeDataChannelInit() const
{
    return nativeDataChannelInit_;
}

RTCDataChannelConfiguration::RTCDataChannelConfiguration(QObject *parent)
    : QObject{parent}, d_ptr{new RTCDataChannelConfigurationPrivate}
{
}

bool RTCDataChannelConfiguration::isOrdered() const
{
    return d_ptr->nativeDataChannelInit_.ordered;
}

void RTCDataChannelConfiguration::setIsOrdered(bool ordered)
{
    d_ptr->nativeDataChannelInit_.ordered = ordered;
}

int RTCDataChannelConfiguration::maxRetransmitTimeMs() const
{
    return d_ptr->maxPacketLifeTime_;
}

void RTCDataChannelConfiguration::setMaxRetransmitTimeMs(int time)
{
    d_ptr->maxPacketLifeTime_ = time;
}

int RTCDataChannelConfiguration::maxPacketLifeTime() const
{
    return *d_ptr->nativeDataChannelInit_.maxRetransmitTime;
}

void RTCDataChannelConfiguration::setMaxPacketLifeTime(int time)
{
    d_ptr->nativeDataChannelInit_.maxRetransmitTime = time;
}

int RTCDataChannelConfiguration::maxRetransmits() const
{
    if (d_ptr->nativeDataChannelInit_.maxRetransmits)
    {
        return *d_ptr->nativeDataChannelInit_.maxRetransmits;
    }
    else
    {
        return -1;
    }
}

void RTCDataChannelConfiguration::setMaxRetransmits(int retransmits)
{
    d_ptr->nativeDataChannelInit_.maxRetransmits = retransmits;
}

bool RTCDataChannelConfiguration::isNegotiated() const
{
    return d_ptr->nativeDataChannelInit_.negotiated;
}

void RTCDataChannelConfiguration::setIsNegotiated(bool negotiated)
{
    d_ptr->nativeDataChannelInit_.negotiated = negotiated;
}

int RTCDataChannelConfiguration::streamId() const
{
    return d_ptr->channelId_;
}

void RTCDataChannelConfiguration::setStreamId(int id)
{
    d_ptr->channelId_ = id;
}

int RTCDataChannelConfiguration::channelId() const
{
    return d_ptr->nativeDataChannelInit_.id;
}

void RTCDataChannelConfiguration::setChannelId(int id)
{
    d_ptr->nativeDataChannelInit_.id = id;
}

QString RTCDataChannelConfiguration::protocol() const
{
    return QString::fromStdString(d_ptr->nativeDataChannelInit_.protocol);
}

void RTCDataChannelConfiguration::setProtocol(const QString &protocol)
{
    d_ptr->nativeDataChannelInit_.protocol = protocol.toStdString();
}
