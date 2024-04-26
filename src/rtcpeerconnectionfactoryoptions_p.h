#ifndef RTCPEERCONNECTIONFACTORYOPTIONS_P_H
#define RTCPEERCONNECTIONFACTORYOPTIONS_P_H

#include "rtcpeerconnectionfactoryoptions.h"

#include <QString>

#include "rtc_base/network_constants.h"
#include "api/peer_connection_interface.h"

class RTCPeerConnectionFactoryOptionsPrivate
{
  public:
    RTCPeerConnectionFactoryOptionsPrivate();
    webrtc::PeerConnectionFactoryInterface::Options nativePeerConnectionFactoryOptions() const;

    bool disableEncryption_{false};
    bool disableNetworkMonitor_{false};
    bool ignoreLoopbackNetworkAdapter_{false};
    bool ignoreVPNNetworkAdapter_{false};
    bool ignoreCellularNetworkAdapter_{false};
    bool ignoreWiFiNetworkAdapter_{false};
    bool ignoreEthernetNetworkAdapter_{false};
};

#endif // RTCPEERCONNECTIONFACTORYOPTIONS_P_H
