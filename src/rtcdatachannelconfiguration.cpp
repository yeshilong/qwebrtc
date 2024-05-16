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
    Q_D(const RTCDataChannelConfiguration);
    return d->nativeDataChannelInit_.ordered;
}

void RTCDataChannelConfiguration::setIsOrdered(bool ordered)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.ordered = ordered;
}

int RTCDataChannelConfiguration::maxRetransmitTimeMs() const
{
    Q_D(const RTCDataChannelConfiguration);
    return d->maxPacketLifeTime_;
}

void RTCDataChannelConfiguration::setMaxRetransmitTimeMs(int time)
{
    Q_D(RTCDataChannelConfiguration);
    d->maxPacketLifeTime_ = time;
}

int RTCDataChannelConfiguration::maxPacketLifeTime() const
{
    Q_D(const RTCDataChannelConfiguration);
    return *d->nativeDataChannelInit_.maxRetransmitTime;
}

void RTCDataChannelConfiguration::setMaxPacketLifeTime(int time)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.maxRetransmitTime = time;
}

int RTCDataChannelConfiguration::maxRetransmits() const
{
    Q_D(const RTCDataChannelConfiguration);
    if (d->nativeDataChannelInit_.maxRetransmits)
    {
        return *d->nativeDataChannelInit_.maxRetransmits;
    }
    else
    {
        return -1;
    }
}

void RTCDataChannelConfiguration::setMaxRetransmits(int retransmits)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.maxRetransmits = retransmits;
}

bool RTCDataChannelConfiguration::isNegotiated() const
{
    Q_D(const RTCDataChannelConfiguration);
    return d->nativeDataChannelInit_.negotiated;
}

void RTCDataChannelConfiguration::setIsNegotiated(bool negotiated)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.negotiated = negotiated;
}

int RTCDataChannelConfiguration::streamId() const
{
    Q_D(const RTCDataChannelConfiguration);
    return d->channelId_;
}

void RTCDataChannelConfiguration::setStreamId(int id)
{
    Q_D(RTCDataChannelConfiguration);
    d->channelId_ = id;
}

int RTCDataChannelConfiguration::channelId() const
{
    Q_D(const RTCDataChannelConfiguration);
    return d->nativeDataChannelInit_.id;
}

void RTCDataChannelConfiguration::setChannelId(int id)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.id = id;
}

QString RTCDataChannelConfiguration::protocol() const
{
    Q_D(const RTCDataChannelConfiguration);
    return QString::fromStdString(d->nativeDataChannelInit_.protocol);
}

void RTCDataChannelConfiguration::setProtocol(const QString &protocol)
{
    Q_D(RTCDataChannelConfiguration);
    d->nativeDataChannelInit_.protocol = protocol.toStdString();
}
