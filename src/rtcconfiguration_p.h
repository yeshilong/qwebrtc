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

#ifndef RTCCONFIGURATION_P_H
#define RTCCONFIGURATION_P_H

#include "rtcconfiguration.h"

#include "api/peer_connection_interface.h"

class RTCConfigurationPrivate
{
  public:
    explicit RTCConfigurationPrivate();
    explicit RTCConfigurationPrivate(
        const webrtc::PeerConnectionInterface::RTCConfiguration &nativeConfiguration);
    void initialize(const webrtc::PeerConnectionInterface::RTCConfiguration &config);
    webrtc::PeerConnectionInterface::RTCConfiguration *createNativeConfiguration() const;

    webrtc::TurnCustomizer *turnCustomizer_ = nullptr;

    bool enableDscp_;
    QVector<RTCIceServer *> iceServers_;
    RTCCertificate *certificate_;
    RTCIceTransportPolicy iceTransportPolicy_;
    RTCBundlePolicy bundlePolicy_;
    RTCRtcpMuxPolicy rtcpMuxPolicy_;
    RTCTcpCandidatePolicy tcpCandidatePolicy_;
    RTCCandidateNetworkPolicy candidateNetworkPolicy_;
    RTCContinualGatheringPolicy continualGatheringPolicy_;
    bool disableIPV6OnWiFi_;
    int maxIPv6Networks_;
    bool disableLinkLocalNetworks_;
    int audioJitterBufferMaxPackets_;
    bool audioJitterBufferFastAccelerate_;
    int iceConnectionReceivingTimeout_;
    int iceBackupCandidatePairPingInterval_;
    RTCEncryptionKeyType keyType_;
    int iceCandidatePoolSize_;
    bool shouldPruneTurnPorts_;
    bool shouldPresumeWritableWhenFullyRelayed_;
    bool shouldSurfaceIceCandidatesOnIceTransportTypeChanged_;
    QVariant iceCheckMinInterval_;
    RTCSdpSemantics sdpSemantics_;
    bool activeResetSrtpParams_;
    bool allowCodecSwitching_;
    RTCCryptoOptions *cryptoOptions_;
    QString turnLoggingId_;
    int rtcpAudioReportIntervalMs_;
    int rtcpVideoReportIntervalMs_;
    bool enableImplicitRollback_;
    bool offerExtmapAllowMixed_;
    QVariant iceCheckIntervalStrongConnectivity_;
    QVariant iceCheckIntervalWeakConnectivity_;
    QVariant iceUnwritableTimeout_;
    QVariant iceUnwritableMinChecks_;
    QVariant iceInactiveTimeout_;
    bool enableIceGatheringOnAnyAddressPorts_;
};

#endif // RTCCONFIGURATION_P_H
