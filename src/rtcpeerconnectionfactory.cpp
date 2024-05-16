#include "rtcpeerconnectionfactory.h"

RTCPeerConnectionFactory::RTCPeerConnectionFactory(QObject *parent) : QObject{parent}
{
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(RTCPeerConnectionFactoryPrivate &d,
                                                   QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}
