#ifndef RTCCONFIGURATION_H
#define RTCCONFIGURATION_H

#include <QObject>
#include <QVector>

#include "rtctypes.h"

#include "rtccertificate.h"
#include "rtccryptooptions.h"
#include "rtciceserver.h"

/**
 * @brief Represents the RTCConfiguration.
 */
class RTCConfiguration : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     */
    explicit RTCConfiguration(QObject *parent = nullptr);

    /**
     * @brief Gets and sets the DSCP codes on outgoing packets.
     * @return The DSCP codes.
     */
    bool enableDscp() const;
    void setEnableDscp(bool enableDscp);

    /**
     * @brief Gets and sets the Ice Servers available to be used by ICE.
     * @return The Ice Servers.
     */
    QVector<RTCIceServer> iceServers() const;
    void setIceServers(const QVector<RTCIceServer> &iceServers);

    /**
     * @brief Gets and sets the RTCCertificate for 're' use.
     * @return The RTCCertificate.
     */
    RTCCertificate certificate() const;
    void setCertificate(const RTCCertificate &certificate);

    /**
     * @brief Gets and sets the candidates the ICE agent is allowed to use.
     * @return The ICE transport policy.
     */
    RTCIceTransportPolicy iceTransportPolicy() const;
    void setIceTransportPolicy(const RTCIceTransportPolicy &iceTransportPolicy);

    /**
     * @brief Gets and sets the media-bundling policy to use when gathering ICE candidates.
     * @return The bundle policy.
     */
    RTCBundlePolicy bundlePolicy() const;
    void setBundlePolicy(const RTCBundlePolicy &bundlePolicy);

    /**
     * @brief Gets and sets the rtcp-mux policy to use when gathering ICE candidates.
     * @return The rtcp-mux policy.
     */
    RTCRtcpMuxPolicy rtcpMuxPolicy() const;
    void setRtcpMuxPolicy(const RTCRtcpMuxPolicy &rtcpMuxPolicy);

    /**
     * @brief Gets and sets the tcp candidate policy to use when gathering ICE candidates.
     * @return The tcp candidate policy.
     */
    RTCTcpCandidatePolicy tcpCandidatePolicy() const;
    void setTcpCandidatePolicy(const RTCTcpCandidatePolicy &tcpCandidatePolicy);

    /**
     * @brief Gets and sets the candidate network policy to use when gathering ICE candidates.
     * @return The candidate network policy.
     */
    RTCCandidateNetworkPolicy candidateNetworkPolicy() const;
    void setCandidateNetworkPolicy(const RTCCandidateNetworkPolicy &candidateNetworkPolicy);

    /**
     * @brief Gets and sets the continual gathering policy to use when gathering ICE candidates.
     * @return The continual gathering policy.
     */
    RTCContinualGatheringPolicy continualGatheringPolicy() const;
    void setContinualGatheringPolicy(const RTCContinualGatheringPolicy &continualGatheringPolicy);

    /**
     * @brief Gets and sets the IPv6 ICE candidates on Wi-Fi.
     * @return The state of IPv6 ICE candidates on Wi-Fi.
     */
    bool disableIPV6OnWiFi() const;
    void setDisableIPV6OnWiFi(bool disableIPV6OnWiFi);

    /**
     * @brief Gets and sets the number of IPv6 network interfaces.
     * @return The number of IPv6 network interfaces.
     */
    int maxIPv6Networks() const;
    void setMaxIPv6Networks(int maxIPv6Networks);

    /**
     * @brief Gets and sets the state of link-local network interfaces.
     * @return The state of link-local network interfaces.
     */
    bool disableLinkLocalNetworks() const;
    void setDisableLinkLocalNetworks(bool disableLinkLocalNetworks);

    /**
     * @brief Gets and sets the maximum packets in the audio jitter buffer.
     * @return The maximum packets in the audio jitter buffer.
     */
    int audioJitterBufferMaxPackets() const;
    void setAudioJitterBufferMaxPackets(int audioJitterBufferMaxPackets);

    /**
     * @brief Gets and sets the state of the audio jitter buffer fast accelerate.
     * @return The state of the audio jitter buffer fast accelerate.
     */
    bool audioJitterBufferFastAccelerate() const;
    void setAudioJitterBufferFastAccelerate(bool audioJitterBufferFastAccelerate);

    /**
     * @brief Gets and sets the ICE connection receiving timeout.
     * @return The ICE connection receiving timeout.
     */
    int iceConnectionReceivingTimeout() const;
    void setIceConnectionReceivingTimeout(int iceConnectionReceivingTimeout);

    /**
     * @brief Gets and sets the ICE backup candidate pair ping interval.
     * @return The ICE backup candidate pair ping interval.
     */
    int iceBackupCandidatePairPingInterval() const;
    void setIceBackupCandidatePairPingInterval(int iceBackupCandidatePairPingInterval);

    /**
     * @brief Gets and sets the key type used to generate SSL identity.
     * @return The key type.
     */
    RTCEncryptionKeyType keyType() const;
    void setKeyType(const RTCEncryptionKeyType &keyType);

    /**
     * @brief Gets and sets the ICE candidate pool size.
     * @return The ICE candidate pool size.
     */
    int iceCandidatePoolSize() const;
    void setIceCandidatePoolSize(int iceCandidatePoolSize);

    /**
     * @brief Gets and sets the state of pruning turn ports.
     * @return The state of pruning turn ports.
     */
    bool shouldPruneTurnPorts() const;
    void setShouldPruneTurnPorts(bool shouldPruneTurnPorts);

    /**
     * @brief Gets and sets the state of presuming writable when fully relayed.
     * @return The state of presuming writable when fully relayed.
     */
    bool shouldPresumeWritableWhenFullyRelayed() const;
    void setShouldPresumeWritableWhenFullyRelayed(bool shouldPresumeWritableWhenFullyRelayed);

    /**
     * @brief Gets and sets the state of surfacing ice candidates on ice transport type changed.
     * @return The state of surfacing ice candidates on ice transport type changed.
     */
    bool shouldSurfaceIceCandidatesOnIceTransportTypeChanged() const;
    void setShouldSurfaceIceCandidatesOnIceTransportTypeChanged(
        bool shouldSurfaceIceCandidatesOnIceTransportTypeChanged);

    /**
     * @brief Gets and sets the minimal interval between consecutive ICE check packets.
     * @return The minimal interval between consecutive ICE check packets.
     */
    int iceCheckMinInterval() const;
    void setIceCheckMinInterval(int iceCheckMinInterval);

    /**
     * @brief Gets and sets the SDP semantics used by this PeerConnection.
     * @return The SDP semantics.
     */
    RTCSdpSemantics sdpSemantics() const;
    void setSdpSemantics(const RTCSdpSemantics &sdpSemantics);

    /**
     * @brief Gets and sets the state of actively resetting the SRTP parameters.
     * @return The state of actively resetting the SRTP parameters.
     */
    bool activeResetSrtpParams() const;
    void setActiveResetSrtpParams(bool activeResetSrtpParams);

    /**
     * @brief Gets and sets the state of allowing codec switching.
     * @return The state of allowing codec switching.
     */
    bool allowCodecSwitching() const;
    void setAllowCodecSwitching(bool allowCodecSwitching);

    /**
     * @brief Gets and sets the advanced optional cryptographic settings related to SRTP and frame encryption.
     * @return The cryptographic settings.
     */
    RTCCryptoOptions cryptoOptions() const;
    void setCryptoOptions(const RTCCryptoOptions &cryptoOptions);

    /**
     * @brief Gets and sets the TurnLoggingId.
     * @return The TurnLoggingId.
     */
    QString turnLoggingId() const;
    void setTurnLoggingId(const QString &turnLoggingId);

    /**
     * @brief Gets and sets the time interval between audio RTCP reports.
     * @return The time interval between audio RTCP reports.
     */
    int rtcpAudioReportIntervalMs() const;
    void setRtcpAudioReportIntervalMs(int rtcpAudioReportIntervalMs);

    /**
     * @brief Gets and sets the time interval between video RTCP reports.
     * @return The time interval between video RTCP reports.
     */
    int rtcpVideoReportIntervalMs() const;
    void setRtcpVideoReportIntervalMs(int rtcpVideoReportIntervalMs);

    /**
     * @brief Gets and sets the state of enabling implicit rollback.
     * @return The state of enabling implicit rollback.
     */
    bool enableImplicitRollback() const;
    void setEnableImplicitRollback(bool enableImplicitRollback);

    /**
     * @brief Gets and sets the state of offering extmap allow mixed.
     * @return The state of offering extmap allow mixed.
     */
    bool offerExtmapAllowMixed() const;
    void setOfferExtmapAllowMixed(bool offerExtmapAllowMixed);

    /**
     * @brief Gets and sets the ICE check interval for strong connectivity.
     * @return The ICE check interval for strong connectivity.
     */
    int iceCheckIntervalStrongConnectivity() const;
    void setIceCheckIntervalStrongConnectivity(int iceCheckIntervalStrongConnectivity);

    /**
     * @brief Gets and sets the ICE check interval for weak connectivity.
     * @return The ICE check interval for weak connectivity.
     */
    int iceCheckIntervalWeakConnectivity() const;
    void setIceCheckIntervalWeakConnectivity(int iceCheckIntervalWeakConnectivity);

    /**
     * @brief Gets and sets the ICE unwritable timeout.
     * @return The ICE unwritable timeout.
     */
    int iceUnwritableTimeout() const;
    void setIceUnwritableTimeout(int iceUnwritableTimeout);

    /**
     * @brief Gets and sets the ICE unwritable minimum checks.
     * @return The ICE unwritable minimum checks.
     */
    int iceUnwritableMinChecks() const;
    void setIceUnwritableMinChecks(int iceUnwritableMinChecks);

    /**
     * @brief Gets and sets the ICE inactive timeout.
     * @return The ICE inactive timeout.
     */
    int iceInactiveTimeout() const;
    void setIceInactiveTimeout(int iceInactiveTimeout);
};

#endif // RTCCONFIGURATION_H
