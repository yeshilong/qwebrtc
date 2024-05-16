/*
 * Copyright (C) 2024 Deltarion Systems
 *
 * This software is licensed under the terms of the GNU Lesser
 * General Public License (LGPL) version 3 as published by the Free
 * Software Foundation. This license is available at:
 * https://www.gnu.org/licenses/lgpl-3.0.html
 *
 * You are free to modify and distribute this software under the
 * terms of the LGPLv3 license. You are required to make the source
 * code of any modifications available under the same license.
 */
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
