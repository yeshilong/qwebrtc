#include "rtcpeerconnectionfactoryoptions.h"

RTCPeerConnectionFactoryOptions::RTCPeerConnectionFactoryOptions(QObject *parent) : QObject{parent}
{
}

bool RTCPeerConnectionFactoryOptions::disableEncryption() const
{
    return disableEncryption_;
}

void RTCPeerConnectionFactoryOptions::setDisableEncryption(bool value)
{
    disableEncryption_ = value;
}

bool RTCPeerConnectionFactoryOptions::disableNetworkMonitor() const
{
    return disableNetworkMonitor_;
}

void RTCPeerConnectionFactoryOptions::setDisableNetworkMonitor(bool value)
{
    disableNetworkMonitor_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreLoopbackNetworkAdapter() const
{
    return ignoreLoopbackNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreLoopbackNetworkAdapter(bool value)
{
    ignoreLoopbackNetworkAdapter_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreVPNNetworkAdapter() const
{
    return ignoreVPNNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreVPNNetworkAdapter(bool value)
{
    ignoreVPNNetworkAdapter_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreCellularNetworkAdapter() const
{
    return ignoreCellularNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreCellularNetworkAdapter(bool value)
{
    ignoreCellularNetworkAdapter_ = value;
}
