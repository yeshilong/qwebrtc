// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
