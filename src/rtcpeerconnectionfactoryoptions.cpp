#include "rtcpeerconnectionfactoryoptions_p.h"

namespace
{

void setNetworkBit(webrtc::PeerConnectionFactoryInterface::Options *options, rtc::AdapterType type,
                   bool ignore)
{
    if (ignore)
    {
        options->network_ignore_mask |= type;
    }
    else
    {
        options->network_ignore_mask &= ~type;
    }
}

} // namespace

RTCPeerConnectionFactoryOptionsPrivate::RTCPeerConnectionFactoryOptionsPrivate()
{
}

webrtc::PeerConnectionFactoryInterface::Options RTCPeerConnectionFactoryOptionsPrivate::
    nativePeerConnectionFactoryOptions() const
{
    webrtc::PeerConnectionFactoryInterface::Options options;

    options.disable_encryption = disableEncryption_;
    options.disable_network_monitor = disableNetworkMonitor_;

    setNetworkBit(&options, rtc::ADAPTER_TYPE_LOOPBACK, ignoreLoopbackNetworkAdapter_);
    setNetworkBit(&options, rtc::ADAPTER_TYPE_VPN, ignoreVPNNetworkAdapter_);
    setNetworkBit(&options, rtc::ADAPTER_TYPE_CELLULAR, ignoreCellularNetworkAdapter_);
    setNetworkBit(&options, rtc::ADAPTER_TYPE_WIFI, ignoreWiFiNetworkAdapter_);
    setNetworkBit(&options, rtc::ADAPTER_TYPE_ETHERNET, ignoreEthernetNetworkAdapter_);

    return options;
}

RTCPeerConnectionFactoryOptions::RTCPeerConnectionFactoryOptions(QObject *parent)
    : QObject{parent}, d_ptr{new RTCPeerConnectionFactoryOptionsPrivate}
{
}

bool RTCPeerConnectionFactoryOptions::disableEncryption() const
{
    Q_D(const RTCPeerConnectionFactoryOptions);
    return d->disableEncryption_;
}

void RTCPeerConnectionFactoryOptions::setDisableEncryption(bool value)
{
    Q_D(RTCPeerConnectionFactoryOptions);
    d->disableEncryption_ = value;
}

bool RTCPeerConnectionFactoryOptions::disableNetworkMonitor() const
{
    Q_D(const RTCPeerConnectionFactoryOptions);
    return d->disableNetworkMonitor_;
}

void RTCPeerConnectionFactoryOptions::setDisableNetworkMonitor(bool value)
{
    Q_D(RTCPeerConnectionFactoryOptions);
    d->disableNetworkMonitor_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreLoopbackNetworkAdapter() const
{
    Q_D(const RTCPeerConnectionFactoryOptions);
    return d->ignoreLoopbackNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreLoopbackNetworkAdapter(bool value)
{
    Q_D(RTCPeerConnectionFactoryOptions);
    d->ignoreLoopbackNetworkAdapter_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreVPNNetworkAdapter() const
{
    Q_D(const RTCPeerConnectionFactoryOptions);
    return d->ignoreVPNNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreVPNNetworkAdapter(bool value)
{
    Q_D(RTCPeerConnectionFactoryOptions);
    d->ignoreVPNNetworkAdapter_ = value;
}

bool RTCPeerConnectionFactoryOptions::ignoreCellularNetworkAdapter() const
{
    Q_D(const RTCPeerConnectionFactoryOptions);
    return d->ignoreCellularNetworkAdapter_;
}

void RTCPeerConnectionFactoryOptions::setIgnoreCellularNetworkAdapter(bool value)
{
    Q_D(RTCPeerConnectionFactoryOptions);
    d->ignoreCellularNetworkAdapter_ = value;
}
