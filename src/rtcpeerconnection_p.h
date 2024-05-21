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
#ifndef RTCPEERCONNECTION_P_H
#define RTCPEERCONNECTION_P_H

#include "rtcpeerconnection.h"

#include "rtclegacystatsreport_p.h"
#include "rtcmediastreamtrack_p.h"
#include "rtcrtpreceiver_p.h"
#include "rtcrtpsender_p.h"
#include "rtcstatisticsreport_p.h"

#include <memory>

#include "rtc_base/checks.h"
#include "api/peer_connection_interface.h"
#include "sdk/media_constraints.h"

namespace webrtc
{

/**
 * These objects are created by RTCPeerConnectionFactory to wrap an
 * id<RTCPeerConnectionDelegate> and call methods on that interface.
 */
class PeerConnectionDelegateAdapter : public PeerConnectionObserver
{
  public:
    explicit PeerConnectionDelegateAdapter(std::shared_ptr<RTCPeerConnection> peerConnection);
    ~PeerConnectionDelegateAdapter() = default;

    void OnSignalingChange(PeerConnectionInterface::SignalingState new_state) override;

    void OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream) override;

    void OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream) override;

    void OnTrack(rtc::scoped_refptr<RtpTransceiverInterface> transceiver) override;

    void OnDataChannel(rtc::scoped_refptr<DataChannelInterface> data_channel) override;

    void OnRenegotiationNeeded() override;

    void OnIceConnectionChange(PeerConnectionInterface::IceConnectionState new_state) override;

    void OnStandardizedIceConnectionChange(
        PeerConnectionInterface::IceConnectionState new_state) override;

    void OnConnectionChange(PeerConnectionInterface::PeerConnectionState new_state) override;

    void OnIceGatheringChange(PeerConnectionInterface::IceGatheringState new_state) override;

    void OnIceCandidate(const IceCandidateInterface *candidate) override;

    void OnIceCandidateError(const std::string &address, int port, const std::string &url,
                             int error_code, const std::string &error_text) override;

    void OnIceCandidatesRemoved(const std::vector<cricket::Candidate> &candidates) override;

    void OnIceSelectedCandidatePairChanged(const cricket::CandidatePairChangeEvent &event) override;

    void OnAddTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver,
                    const std::vector<rtc::scoped_refptr<MediaStreamInterface>> &streams) override;

    void OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver) override;

  private:
    std::weak_ptr<RTCPeerConnection> peer_connection_;
};

class StatsCollectorCallbackAdapter : public RTCStatsCollectorCallback
{
  public:
    explicit StatsCollectorCallbackAdapter(RTCStatisticsCompletionHandler completion_handler)
        : completion_handler_(completion_handler)
    {
    }

    ~StatsCollectorCallbackAdapter() override
    {
        completion_handler_ = nullptr;
    }

    void OnStatsDelivered(const rtc::scoped_refptr<const RTCStatsReport> &report) override
    {
        RTC_DCHECK(completion_handler_);
        auto statisticsReport =
            std::make_shared<RTCStatisticsReport>(*(new RTCStatisticsReportPrivate(*report)));
        completion_handler_(statisticsReport);
        completion_handler_ = nullptr;
    }

  private:
    RTCStatisticsCompletionHandler completion_handler_;
};

class StatsObserverAdapter : public StatsObserver
{
  public:
    explicit StatsObserverAdapter(RTCLegacyStatsReportCompletionHandler completionHandler)
    {
        completion_handler_ = completionHandler;
    }

    ~StatsObserverAdapter() override
    {
        completion_handler_ = nullptr;
    }

    void OnComplete(const StatsReports &reports) override
    {
        RTC_DCHECK(completion_handler_);
        std::vector<std::shared_ptr<RTCLegacyStatsReport>> stats;
        stats.reserve(reports.size());
        for (const auto *report : reports)
        {
            auto statsReport =
                std::make_shared<RTCLegacyStatsReport>(*(new RTCLegacyStatsReportPrivate(*report)));
            stats.push_back(statsReport);
        }
        completion_handler_(stats);
        completion_handler_ = nullptr;
    }

  private:
    RTCLegacyStatsReportCompletionHandler completion_handler_;
};

} // namespace webrtc

class IRTCSSLCertificateVerifier;
class RTCPeerConnectionPrivate
{
  public:
    RTCPeerConnectionPrivate(RTCPeerConnectionFactory *factory, RTCConfiguration *configuration,
                             RTCMediaConstraints *constraints,
                             IRTCSSLCertificateVerifier *certificateVerifier,
                             IRTCPeerConnectionDelegate *delegate);
    RTCPeerConnectionPrivate(RTCPeerConnectionFactory *factory, RTCConfiguration *configuration,
                             RTCMediaConstraints *constraints,
                             std::unique_ptr<webrtc::PeerConnectionDependencies> dependencies,
                             IRTCPeerConnectionDelegate *delegate);

    rtc::scoped_refptr<webrtc::PeerConnectionInterface> nativePeerConnection() const;

    IRTCPeerConnectionDelegate *delegate_;
    RTCPeerConnectionFactory *factory_;
    QVector<RTCMediaStream *> localStreams_;
    std::unique_ptr<webrtc::PeerConnectionDelegateAdapter> observer_;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> nativePeerConnection_;
    std::unique_ptr<webrtc::MediaConstraints> nativeMediaConstraints_;
    bool hasStartedRtcEventLog_;
    RTCPeerConnection *q_ptr;
};

#endif // RTCPEERCONNECTION_P_H
