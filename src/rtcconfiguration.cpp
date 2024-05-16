#include "rtcconfiguration_p.h"

#include "rtcicecandidate.h"
#include "rtciceserver_p.h"

#include "rtc_base/checks.h"
#include "rtc_base/rtc_certificate_generator.h"
#include "rtc_base/ssl_identity.h"

RTCConfigurationPrivate::RTCConfigurationPrivate()
{
    webrtc::PeerConnectionInterface::RTCConfiguration config;
    config.sdp_semantics = webrtc::SdpSemantics::kUnifiedPlan;
    initialize(config);
}

RTCConfigurationPrivate::RTCConfigurationPrivate(
    const webrtc::PeerConnectionInterface::RTCConfiguration &nativeConfiguration)
{
    initialize(nativeConfiguration);
}

void RTCConfigurationPrivate::initialize(
    const webrtc::PeerConnectionInterface::RTCConfiguration &config)
{
    enableDscp_ = config.dscp();
    for (const auto &iceServer : config.servers)
    {
        iceServers_.push_back(new RTCIceServer(*(new RTCIceServerPrivate(iceServer))));
    }
    if (!config.certificates.empty())
    {
        rtc::scoped_refptr<rtc::RTCCertificate> native_cert;
        native_cert = config.certificates[0];
        rtc::RTCCertificatePEM native_pem = native_cert->ToPEM();
        certificate_ = new RTCCertificate(QString::fromStdString(native_pem.private_key()),
                                          QString::fromStdString(native_pem.certificate()));
    }
    iceTransportPolicy_ = static_cast<RTCIceTransportPolicy>(config.type);
    bundlePolicy_ = static_cast<RTCBundlePolicy>(config.bundle_policy);
    rtcpMuxPolicy_ = static_cast<RTCRtcpMuxPolicy>(config.rtcp_mux_policy);
    tcpCandidatePolicy_ = static_cast<RTCTcpCandidatePolicy>(config.tcp_candidate_policy);
    candidateNetworkPolicy_ =
        static_cast<RTCCandidateNetworkPolicy>(config.candidate_network_policy);
    continualGatheringPolicy_ =
        static_cast<RTCContinualGatheringPolicy>(config.continual_gathering_policy);
    disableIPV6OnWiFi_ = config.disable_ipv6_on_wifi;
    maxIPv6Networks_ = config.max_ipv6_networks;
    disableLinkLocalNetworks_ = config.disable_link_local_networks;
    audioJitterBufferMaxPackets_ = config.audio_jitter_buffer_max_packets;
    audioJitterBufferFastAccelerate_ = config.audio_jitter_buffer_fast_accelerate;
    iceConnectionReceivingTimeout_ = config.ice_connection_receiving_timeout;
    iceBackupCandidatePairPingInterval_ = config.ice_backup_candidate_pair_ping_interval;
    keyType_ = RTCEncryptionKeyType::RTCEncryptionKeyTypeECDSA;
    iceCandidatePoolSize_ = config.ice_candidate_pool_size;
    shouldPruneTurnPorts_ = config.prune_turn_ports;
    shouldPresumeWritableWhenFullyRelayed_ = config.presume_writable_when_fully_relayed;
    shouldSurfaceIceCandidatesOnIceTransportTypeChanged_ =
        config.surface_ice_candidates_on_ice_transport_type_changed;
    if (config.ice_check_min_interval)
        iceCheckMinInterval_ = *config.ice_check_min_interval;
    sdpSemantics_ = static_cast<RTCSdpSemantics>(config.sdp_semantics);
    turnCustomizer_ = config.turn_customizer;
    activeResetSrtpParams_ = config.active_reset_srtp_params;
    if (config.crypto_options)
    {
        cryptoOptions_ =
            new RTCCryptoOptions(config.crypto_options->srtp.enable_gcm_crypto_suites,
                                 config.crypto_options->srtp.enable_aes128_sha1_32_crypto_cipher,
                                 config.crypto_options->srtp.enable_encrypted_rtp_header_extensions,
                                 config.crypto_options->sframe.require_frame_encryption);
    }
    turnLoggingId_ = QString::fromStdString(config.turn_logging_id);
    rtcpAudioReportIntervalMs_ = config.audio_rtcp_report_interval_ms();
    rtcpVideoReportIntervalMs_ = config.video_rtcp_report_interval_ms();
    allowCodecSwitching_ = config.allow_codec_switching.value_or(false);
    enableImplicitRollback_ = config.enable_implicit_rollback;
    offerExtmapAllowMixed_ = config.offer_extmap_allow_mixed;
    iceCheckIntervalStrongConnectivity_ =
        config.ice_check_interval_strong_connectivity.has_value()
            ? QVariant(*config.ice_check_interval_strong_connectivity).toInt()
            : QVariant();
    iceCheckIntervalWeakConnectivity_ =
        config.ice_check_interval_weak_connectivity.has_value()
            ? QVariant(*config.ice_check_interval_weak_connectivity).toInt()
            : QVariant();
    iceUnwritableTimeout_ = config.ice_unwritable_timeout.has_value()
                                ? QVariant(*config.ice_unwritable_timeout).toInt()
                                : QVariant();
    iceUnwritableMinChecks_ = config.ice_unwritable_min_checks.has_value()
                                  ? QVariant(*config.ice_unwritable_min_checks).toInt()
                                  : QVariant();
    iceInactiveTimeout_ = config.ice_inactive_timeout.has_value()
                              ? QVariant(*config.ice_inactive_timeout).toInt()
                              : QVariant();
    enableIceGatheringOnAnyAddressPorts_ = config.enable_any_address_ports;
}

webrtc::PeerConnectionInterface::RTCConfiguration *RTCConfigurationPrivate::
    createNativeConfiguration() const
{
    std::unique_ptr<webrtc::PeerConnectionInterface::RTCConfiguration> nativeConfig(
        new webrtc::PeerConnectionInterface::RTCConfiguration(
            webrtc::PeerConnectionInterface::RTCConfigurationType::kAggressive));

    nativeConfig->set_dscp(enableDscp_);
    for (const auto &iceServer : iceServers_)
    {
        nativeConfig->servers.push_back(iceServer->d_ptr->nativeIceServer());
    }
    nativeConfig->type =
        static_cast<webrtc::PeerConnectionInterface::IceTransportsType>(iceTransportPolicy_);
    nativeConfig->bundle_policy =
        static_cast<webrtc::PeerConnectionInterface::BundlePolicy>(bundlePolicy_);
    nativeConfig->rtcp_mux_policy =
        static_cast<webrtc::PeerConnectionInterface::RtcpMuxPolicy>(rtcpMuxPolicy_);
    nativeConfig->tcp_candidate_policy =
        static_cast<webrtc::PeerConnectionInterface::TcpCandidatePolicy>(tcpCandidatePolicy_);
    nativeConfig->candidate_network_policy =
        static_cast<webrtc::PeerConnectionInterface::CandidateNetworkPolicy>(
            candidateNetworkPolicy_);
    nativeConfig->continual_gathering_policy =
        static_cast<webrtc::PeerConnectionInterface::ContinualGatheringPolicy>(
            continualGatheringPolicy_);
    nativeConfig->disable_ipv6_on_wifi = disableIPV6OnWiFi_;
    nativeConfig->max_ipv6_networks = maxIPv6Networks_;
    nativeConfig->disable_link_local_networks = disableLinkLocalNetworks_;
    nativeConfig->audio_jitter_buffer_max_packets = audioJitterBufferMaxPackets_;
    nativeConfig->audio_jitter_buffer_fast_accelerate = audioJitterBufferFastAccelerate_;
    nativeConfig->ice_connection_receiving_timeout = iceConnectionReceivingTimeout_;
    nativeConfig->ice_backup_candidate_pair_ping_interval = iceBackupCandidatePairPingInterval_;

    rtc::KeyType keyType = static_cast<rtc::KeyType>(keyType_);
    if (certificate_ != nullptr)
    {
        // if offered a pemcert use it...
        RTC_LOG(LS_INFO) << "Have configured cert - using it.";
        std::string pem_private_key = certificate_->privateKey().toStdString();
        std::string pem_certificate = certificate_->certificate().toStdString();
        rtc::RTCCertificatePEM pem = rtc::RTCCertificatePEM(pem_private_key, pem_certificate);
        rtc::scoped_refptr<rtc::RTCCertificate> certificate = rtc::RTCCertificate::FromPEM(pem);
        RTC_LOG(LS_INFO) << "Created cert from PEM strings.";
        if (!certificate)
        {
            RTC_LOG(LS_ERROR) << "Failed to generate certificate from PEM.";
            return nullptr;
        }
        nativeConfig->certificates.push_back(certificate);
    }
    else
    {
        RTC_LOG(LS_INFO) << "Don't have configured cert.";
        // Generate non-default certificate.
        if (keyType != rtc::KT_DEFAULT)
        {
            rtc::scoped_refptr<rtc::RTCCertificate> certificate =
                rtc::RTCCertificateGenerator::GenerateCertificate(rtc::KeyParams(keyType),
                                                                  absl::optional<uint64_t>());
            if (!certificate)
            {
                RTC_LOG(LS_ERROR) << "Failed to generate certificate.";
                return nullptr;
            }
            nativeConfig->certificates.push_back(certificate);
        }
    }

    nativeConfig->ice_candidate_pool_size = iceCandidatePoolSize_;
    nativeConfig->prune_turn_ports = shouldPruneTurnPorts_;
    nativeConfig->presume_writable_when_fully_relayed = shouldPresumeWritableWhenFullyRelayed_;
    nativeConfig->surface_ice_candidates_on_ice_transport_type_changed =
        shouldSurfaceIceCandidatesOnIceTransportTypeChanged_;
    if (iceCheckMinInterval_.isValid())
        nativeConfig->ice_check_min_interval = absl::optional<int>(iceCheckMinInterval_.toInt());
    nativeConfig->sdp_semantics = static_cast<webrtc::SdpSemantics>(sdpSemantics_);
    if (turnCustomizer_)
    {
        nativeConfig->turn_customizer = turnCustomizer_;
    }
    nativeConfig->active_reset_srtp_params = activeResetSrtpParams_;
    if (cryptoOptions_)
    {
        webrtc::CryptoOptions nativeCryptoOptions;
        nativeCryptoOptions.srtp.enable_gcm_crypto_suites =
            cryptoOptions_->srtpEnableGcmCryptoSuites() ? true : false;
        nativeCryptoOptions.srtp.enable_aes128_sha1_32_crypto_cipher =
            cryptoOptions_->srtpEnableAes128Sha1_32CryptoCipher() ? true : false;
        nativeCryptoOptions.srtp.enable_encrypted_rtp_header_extensions =
            cryptoOptions_->srtpEnableEncryptedRtpHeaderExtensions() ? true : false;
        nativeCryptoOptions.sframe.require_frame_encryption =
            cryptoOptions_->sframeRequireFrameEncryption() ? true : false;
        nativeConfig->crypto_options = absl::optional<webrtc::CryptoOptions>(nativeCryptoOptions);
    }
    nativeConfig->turn_logging_id = turnLoggingId_.toStdString();
    nativeConfig->set_audio_rtcp_report_interval_ms(rtcpAudioReportIntervalMs_);
    nativeConfig->set_video_rtcp_report_interval_ms(rtcpVideoReportIntervalMs_);
    nativeConfig->allow_codec_switching = allowCodecSwitching_;
    nativeConfig->enable_implicit_rollback = enableImplicitRollback_;
    nativeConfig->offer_extmap_allow_mixed = offerExtmapAllowMixed_;
    if (iceCheckIntervalStrongConnectivity_.isValid())
        nativeConfig->ice_check_interval_strong_connectivity =
            absl::optional<int>(iceCheckIntervalStrongConnectivity_.toInt());
    if (iceCheckIntervalWeakConnectivity_.isValid())
        nativeConfig->ice_check_interval_weak_connectivity =
            absl::optional<int>(iceCheckIntervalWeakConnectivity_.toInt());
    if (iceUnwritableTimeout_.isValid())
        nativeConfig->ice_unwritable_timeout = absl::optional<int>(iceUnwritableTimeout_.toInt());
    if (iceUnwritableMinChecks_.isValid())
        nativeConfig->ice_unwritable_min_checks =
            absl::optional<int>(iceUnwritableMinChecks_.toInt());
    if (iceInactiveTimeout_.isValid())
        nativeConfig->ice_inactive_timeout = absl::optional<int>(iceInactiveTimeout_.toInt());
    nativeConfig->enable_any_address_ports = enableIceGatheringOnAnyAddressPorts_;

    return nativeConfig.release();
}

RTCConfiguration::RTCConfiguration(QObject *parent)
    : QObject{parent}, d_ptr{new RTCConfigurationPrivate{}}
{
}

RTCConfiguration::RTCConfiguration(RTCConfigurationPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}
