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

#ifndef RTCPEERCONNECTIONFACTORYOPTIONS_H
#define RTCPEERCONNECTIONFACTORYOPTIONS_H

#include <QObject>

class RTCPeerConnectionFactoryOptionsPrivate;
/**
 * @brief Represents options used for configuring the behavior of the RTCPeerConnectionFactory.
 */
class RTCPeerConnectionFactoryOptions : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an instance of the RTCPeerConnectionFactoryOptions class.
     * @param parent The parent object.
     */
    explicit RTCPeerConnectionFactoryOptions(QObject *parent = nullptr);

    /**
     * @brief Gets whether encryption is disabled.
     * @return True if encryption is disabled, false otherwise.
     */
    bool disableEncryption() const;

    /**
     * @brief Sets whether to disable encryption.
     * @param value True to disable encryption, false to enable it.
     */
    void setDisableEncryption(bool value);

    /**
     * @brief Gets whether network monitoring is disabled.
     * @return True if network monitoring is disabled, false otherwise.
     */
    bool disableNetworkMonitor() const;

    /**
     * @brief Sets whether to disable network monitoring.
     * @param value True to disable network monitoring, false to enable it.
     */
    void setDisableNetworkMonitor(bool value);

    /**
     * @brief Gets whether the loopback network adapter is ignored.
     * @return True if the loopback network adapter is ignored, false otherwise.
     */
    bool ignoreLoopbackNetworkAdapter() const;

    /**
     * @brief Sets whether to ignore the loopback network adapter.
     * @param value True to ignore the loopback network adapter, false to consider it.
     */
    void setIgnoreLoopbackNetworkAdapter(bool value);

    /**
     * @brief Gets whether the VPN network adapter is ignored.
     * @return True if the VPN network adapter is ignored, false otherwise.
     */
    bool ignoreVPNNetworkAdapter() const;

    /**
     * @brief Sets whether to ignore the VPN network adapter.
     * @param value True to ignore the VPN network adapter, false to consider it.
     */
    void setIgnoreVPNNetworkAdapter(bool value);

    /**
     * @brief Gets whether the cellular network adapter is ignored.
     * @return True if the cellular network adapter is ignored, false otherwise.
     */
    bool ignoreCellularNetworkAdapter() const;

    /**
     * @brief Sets whether to ignore the cellular network adapter.
     * @param value True to ignore the cellular network adapter, false to consider it.
     */
    void setIgnoreCellularNetworkAdapter(bool value);

    /**
     * @brief Gets whether the WiFi network adapter is ignored.
     * @return True if the WiFi network adapter is ignored, false otherwise.
     */
    bool ignoreWiFiNetworkAdapter() const;

    /**
     * @brief Sets whether to ignore the WiFi network adapter.
     * @param value True to ignore the WiFi network adapter, false to consider it.
     */
    void setIgnoreWiFiNetworkAdapter(bool value);

    /**
     * @brief Gets whether the Ethernet network adapter is ignored.
     * @return True if the Ethernet network adapter is ignored, false otherwise.
     */
    bool ignoreEthernetNetworkAdapter() const;

    /**
     * @brief Sets whether to ignore the Ethernet network adapter.
     * @param value True to ignore the Ethernet network adapter, false to consider it.
     */
    void setIgnoreEthernetNetworkAdapter(bool value);

  private:
    RTCPeerConnectionFactoryOptionsPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCPeerConnectionFactoryOptions)

    friend class RTCPeerConnectionFactory;
};

#endif // RTCPEERCONNECTIONFACTORYOPTIONS_H
