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

#include "rtcpeerconnection_p.h"

#include "rtcerror_p.h"
#include "rtclogging.h"
#include "rtcpeerconnectiondelegate.h"
#include "rtcsessiondescription_p.h"
#include "rtcmediastreamtrack_p.h"
#include "rtcmediastream_p.h"
#include "rtcmediaconstraints_p.h"
#include "rtcrtptransceiver_p.h"
#include "rtcrtptransceiverinit_p.h"
#include "rtcdatachannel_p.h"
#include "rtcicecandidate_p.h"
#include "rtcicecandidateerrorevent.h"
#include "rtcrtpreceiver_p.h"
#include "rtcconfiguration_p.h"
#include "rtcpeerconnectionfactory_p.h"
#include "rtcdatachannelconfiguration_p.h"
#include "rtcdatachannel_p.h"

#include <memory>

#include "api/jsep_ice_candidate.h"
#include "api/rtc_event_log_output_file.h"
#include "api/set_local_description_observer_interface.h"
#include "api/set_remote_description_observer_interface.h"
#include "rtc_base/checks.h"
#include "rtc_base/numerics/safe_conversions.h"
#include "native/ssl_certificate_verifier.h"

namespace
{

class SetSessionDescriptionObserver : public webrtc::SetLocalDescriptionObserverInterface,
                                      public webrtc::SetRemoteDescriptionObserverInterface
{
  public:
    SetSessionDescriptionObserver(RTCSetSessionDescriptionCompletionHandler completionHandler)
    {
        completion_handler_ = completionHandler;
    }

    virtual void OnSetLocalDescriptionComplete(webrtc::RTCError error) override
    {
        OnCompelete(error);
    }

    virtual void OnSetRemoteDescriptionComplete(webrtc::RTCError error) override
    {
        OnCompelete(error);
    }

  private:
    void OnCompelete(webrtc::RTCError error)
    {
        RTC_DCHECK(completion_handler_ != nullptr);
        if (error.ok())
        {
            completion_handler_(nullptr);
        }
        else
        {
            RTCErrorPrivate *err = new RTCErrorPrivate(error);
            completion_handler_(new RTCError(*err));
        }
        completion_handler_ = nullptr;
    }
    RTCSetSessionDescriptionCompletionHandler completion_handler_;
};

} // anonymous namespace

namespace webrtc
{

class CreateSessionDescriptionObserverAdapter : public CreateSessionDescriptionObserver
{
  public:
    CreateSessionDescriptionObserverAdapter(
        RTCCreateSessionDescriptionCompletionHandler completionHandler)
    {
        completion_handler_ = completionHandler;
    }

    ~CreateSessionDescriptionObserverAdapter() override
    {
        completion_handler_ = nullptr;
    }

    void OnSuccess(SessionDescriptionInterface *desc) override
    {
        RTC_DCHECK(completion_handler_);
        std::unique_ptr<webrtc::SessionDescriptionInterface> description =
            std::unique_ptr<webrtc::SessionDescriptionInterface>(desc);
        RTCSessionDescriptionPrivate *privateSession =
            new RTCSessionDescriptionPrivate(description.get());
        RTCSessionDescription *sessionDescription = new RTCSessionDescription(*privateSession);
        completion_handler_(sessionDescription, nullptr);
        completion_handler_ = nullptr;
    }

    void OnFailure(webrtc::RTCError error) override
    {
        RTC_DCHECK(completion_handler_);
        RTCErrorPrivate *privateErr = new RTCErrorPrivate(error);
        completion_handler_(nullptr, new ::RTCError(*privateErr));
        completion_handler_ = nullptr;
    }

  private:
    RTCCreateSessionDescriptionCompletionHandler completion_handler_;
};

PeerConnectionDelegateAdapter::PeerConnectionDelegateAdapter(
    std::shared_ptr<RTCPeerConnection> peerConnection)
{
    peer_connection_ = peerConnection;
}

void PeerConnectionDelegateAdapter::OnSignalingChange(
    PeerConnectionInterface::SignalingState new_state)
{
    RTCSignalingState state = static_cast<RTCSignalingState>(new_state);
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeSignalingState(peer_connection.get(), state);
    }
}

void PeerConnectionDelegateAdapter::OnAddStream(rtc::scoped_refptr<MediaStreamInterface> stream)
{
    auto peer_connection = peer_connection_.lock();

    RTCMediaStream *mediaStream =
        new RTCMediaStream(*(new RTCMediaStreamPrivate(peer_connection->d_ptr->factory_, stream)));
    if (peer_connection)
    {
        peer_connection->delegate()->didAddStream(peer_connection.get(), mediaStream);
    }
}

void PeerConnectionDelegateAdapter::OnRemoveStream(rtc::scoped_refptr<MediaStreamInterface> stream)
{
    auto peer_connection = peer_connection_.lock();
    RTCMediaStream *mediaStream =
        new RTCMediaStream(*(new RTCMediaStreamPrivate(peer_connection->d_ptr->factory_, stream)));
    if (peer_connection)
    {
        peer_connection->delegate()->didRemoveStream(peer_connection.get(), mediaStream);
    }
}

void PeerConnectionDelegateAdapter::OnTrack(
    rtc::scoped_refptr<RtpTransceiverInterface> nativeTransceiver)
{
    auto peer_connection = peer_connection_.lock();
    RTCRtpTransceiver *transceiver = new RTCRtpTransceiver(
        *(new RTCRtpTransceiverPrivate(peer_connection->d_ptr->factory_, nativeTransceiver)));
    if (peer_connection)
    {
        peer_connection->delegate()->didStartReceivingOnTransceiver(peer_connection.get(),
                                                                    transceiver);
    }
}

void PeerConnectionDelegateAdapter::OnDataChannel(
    rtc::scoped_refptr<DataChannelInterface> data_channel)
{
    auto peer_connection = peer_connection_.lock();
    RTCDataChannel *dataChannel = new RTCDataChannel(
        *(new RTCDataChannelPrivate(peer_connection->d_ptr->factory_, data_channel)));
    if (peer_connection)
    {
        peer_connection->delegate()->didOpenDataChannel(peer_connection.get(), dataChannel);
    }
}

void PeerConnectionDelegateAdapter::OnRenegotiationNeeded()
{
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->peerConnectionShouldNegotiate(peer_connection.get());
    }
}

void PeerConnectionDelegateAdapter::OnIceConnectionChange(
    PeerConnectionInterface::IceConnectionState new_state)
{
    auto peer_connection = peer_connection_.lock();
    RTCIceConnectionState state = static_cast<RTCIceConnectionState>(new_state);
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeIceConnectionState(peer_connection.get(), state);
    }
}

void PeerConnectionDelegateAdapter::OnStandardizedIceConnectionChange(
    PeerConnectionInterface::IceConnectionState new_state)
{
    RTCIceConnectionState state = static_cast<RTCIceConnectionState>(new_state);
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeStandardizedIceConnectionState(peer_connection.get(),
                                                                             state);
    }
}

void PeerConnectionDelegateAdapter::OnConnectionChange(
    PeerConnectionInterface::PeerConnectionState new_state)
{
    RTCPeerConnectionState state = static_cast<RTCPeerConnectionState>(new_state);
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeConnectionState(peer_connection.get(), state);
    }
}

void PeerConnectionDelegateAdapter::OnIceGatheringChange(
    PeerConnectionInterface::IceGatheringState new_state)
{
    RTCIceGatheringState state = static_cast<RTCIceGatheringState>(new_state);
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeIceGatheringState(peer_connection.get(), state);
    }
}

void PeerConnectionDelegateAdapter::OnIceCandidate(const IceCandidateInterface *candidate)
{
    RTCIceCandidate *iceCandidate = new RTCIceCandidate(*(new RTCIceCandidatePrivate(candidate)));
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didGenerateIceCandidate(peer_connection.get(), iceCandidate);
    }
}

void PeerConnectionDelegateAdapter::OnIceCandidateError(const std::string &address, int port,
                                                        const std::string &url, int error_code,
                                                        const std::string &error_text)
{
    auto peer_connection = peer_connection_.lock();
    RTCIceCandidateErrorEvent *event = new RTCIceCandidateErrorEvent(
        QString::fromStdString(address), port, QString::fromStdString(url), error_code,
        QString::fromStdString(error_text));
    if (peer_connection)
    {
        peer_connection->delegate()->didFailToGatherIceCandidate(peer_connection.get(), event);
    }
}

void PeerConnectionDelegateAdapter::OnIceCandidatesRemoved(
    const std::vector<cricket::Candidate> &candidates)
{
    QVector<RTCIceCandidate *> iceCandidates = {};
    for (const auto &candidate : candidates)
    {
        std::unique_ptr<JsepIceCandidate> candidateWrapper(
            new JsepIceCandidate(candidate.transport_name(), -1, candidate));
        RTCIceCandidate *iceCandidate =
            new RTCIceCandidate(*(new RTCIceCandidatePrivate(candidateWrapper.get())));
        iceCandidates.append(iceCandidate);
    }
    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didRemoveIceCandidates(peer_connection.get(), iceCandidates);
    }
}

void PeerConnectionDelegateAdapter::OnIceSelectedCandidatePairChanged(
    const cricket::CandidatePairChangeEvent &event)
{
    const auto &selected_pair = event.selected_candidate_pair;

    auto localCandidateWrapper = std::make_unique<JsepIceCandidate>(
        selected_pair.local_candidate().transport_name(), -1, selected_pair.local_candidate());
    RTCIceCandidate *localCandidate =
        new RTCIceCandidate(*(new RTCIceCandidatePrivate(localCandidateWrapper.release())));
    auto remoteCandidateWrapper = std::make_unique<JsepIceCandidate>(
        selected_pair.remote_candidate().transport_name(), -1, selected_pair.remote_candidate());
    RTCIceCandidate *remoteCandidate =
        new RTCIceCandidate(*(new RTCIceCandidatePrivate(remoteCandidateWrapper.release())));

    QString reason = QString::fromStdString(event.reason);

    auto peer_connection = peer_connection_.lock();
    if (peer_connection)
    {
        peer_connection->delegate()->didChangeLocalCandidate(peer_connection.get(), localCandidate,
                                                             remoteCandidate,
                                                             event.last_data_received_ms, reason);
    }
}

void PeerConnectionDelegateAdapter::OnAddTrack(
    rtc::scoped_refptr<RtpReceiverInterface> receiver,
    const std::vector<rtc::scoped_refptr<MediaStreamInterface>> &streams)
{
    auto peer_connection = peer_connection_.lock();
    QVector<RTCMediaStream *> mediaStreams = {};

    for (const auto &nativeStream : streams)
    {
        RTCMediaStream *mediaStream = new RTCMediaStream(
            *(new RTCMediaStreamPrivate(peer_connection->d_ptr->factory_, nativeStream)));
        mediaStreams.append(mediaStream);
    }
    RTCRtpReceiver *rtpReceiver = new RTCRtpReceiver(
        *(new RTCRtpReceiverPrivate(peer_connection->d_ptr->factory_, receiver)));

    if (peer_connection)
    {
        peer_connection->delegate()->didAddReceiver(peer_connection.get(), rtpReceiver,
                                                    mediaStreams);
    }
}

void PeerConnectionDelegateAdapter::OnRemoveTrack(rtc::scoped_refptr<RtpReceiverInterface> receiver)
{
    auto peer_connection = peer_connection_.lock();
    RTCRtpReceiver *rtpReceiver = new RTCRtpReceiver(
        *(new RTCRtpReceiverPrivate(peer_connection->d_ptr->factory_, receiver)));
    if (peer_connection)
    {
        peer_connection->delegate()->didRemoveReceiver(peer_connection.get(), rtpReceiver);
    }
}

} // namespace webrtc

rtc::scoped_refptr<webrtc::PeerConnectionInterface> RTCPeerConnectionPrivate::nativePeerConnection()
    const
{
    return nativePeerConnection_;
}
RTCPeerConnectionPrivate::RTCPeerConnectionPrivate(RTCPeerConnectionFactory *factory,
                                                   RTCConfiguration *configuration,
                                                   RTCMediaConstraints *constraints,
                                                   IRTCSSLCertificateVerifier *certificateVerifier,
                                                   IRTCPeerConnectionDelegate *delegate)
{
    Q_ASSERT(factory);
    std::unique_ptr<webrtc::PeerConnectionDependencies> dependencies =
        std::make_unique<webrtc::PeerConnectionDependencies>(nullptr);
    if (certificateVerifier != nullptr)
    {
        dependencies->tls_cert_verifier =
            webrtc::ObjCToNativeCertificateVerifier(certificateVerifier);
    }
}
RTCPeerConnectionPrivate::RTCPeerConnectionPrivate(
    RTCPeerConnectionFactory *factory, RTCConfiguration *configuration,
    RTCMediaConstraints *constraints,
    std::unique_ptr<webrtc::PeerConnectionDependencies> dependencies,
    IRTCPeerConnectionDelegate *delegate)
{
    Q_ASSERT(factory);
    Q_ASSERT(configuration);
    Q_ASSERT(delegate);

    std::unique_ptr<webrtc::PeerConnectionInterface::RTCConfiguration> config(
        configuration->d_ptr->createNativeConfiguration());
    Q_ASSERT(config.get());

    observer_.reset(
        new webrtc::PeerConnectionDelegateAdapter(std::shared_ptr<RTCPeerConnection>(this->q_ptr)));
    nativeMediaConstraints_ = constraints->d_ptr->nativeMediaConstraints();
    CopyConstraintsIntoRtcConfiguration(nativeMediaConstraints_.get(), config.get());

    webrtc::PeerConnectionDependencies deps = std::move(*dependencies.release());
    deps.observer = observer_.get();
    auto result = factory->d_ptr->nativePeerConnectionFactory()->CreatePeerConnectionOrError(
        *config, std::move(deps));

    if (!result.ok())
    {
    }
    nativePeerConnection_ = result.MoveValue();
    factory_ = factory;
    localStreams_ = {};
    delegate_ = delegate;
}

RTCPeerConnection::RTCPeerConnection(QObject *parent) : QObject{parent}
{
}

RTCPeerConnection::RTCPeerConnection(RTCPeerConnectionPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
    d_ptr->q_ptr = this;
}

IRTCPeerConnectionDelegate *RTCPeerConnection::delegate()
{
    Q_D(RTCPeerConnection);
    return d->delegate_;
}

QVector<RTCMediaStream *> RTCPeerConnection::localStreams()
{
    Q_D(RTCPeerConnection);
    return d->localStreams_;
}

RTCSessionDescription *RTCPeerConnection::localDescription()
{
    Q_D(RTCPeerConnection);
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread.
    return d->nativePeerConnection_->signaling_thread()->BlockingCall([d] {
        const webrtc::SessionDescriptionInterface *description =
            d->nativePeerConnection_->local_description();
        return description
                   ? new RTCSessionDescription(*(new RTCSessionDescriptionPrivate(description)))
                   : nullptr;
    });
}

RTCSessionDescription *RTCPeerConnection::remoteDescription()
{
    Q_D(RTCPeerConnection);
    // It's only safe to operate on SessionDescriptionInterface on the signaling thread.
    return d->nativePeerConnection_->signaling_thread()->BlockingCall([d] {
        const webrtc::SessionDescriptionInterface *description =
            d->nativePeerConnection_->remote_description();
        return description
                   ? new RTCSessionDescription(*(new RTCSessionDescriptionPrivate(description)))
                   : nullptr;
    });
}

RTCSignalingState RTCPeerConnection::signalingState()
{
    Q_D(RTCPeerConnection);
    return static_cast<RTCSignalingState>(d->nativePeerConnection_->signaling_state());
}

RTCIceConnectionState RTCPeerConnection::iceConnectionState()
{
    Q_D(RTCPeerConnection);
    return static_cast<RTCIceConnectionState>(d->nativePeerConnection_->ice_connection_state());
}

RTCPeerConnectionState RTCPeerConnection::connectionState()
{
    Q_D(RTCPeerConnection);
    return static_cast<RTCPeerConnectionState>(d->nativePeerConnection_->peer_connection_state());
}

RTCIceGatheringState RTCPeerConnection::iceGatheringState()
{
    Q_D(RTCPeerConnection);
    return static_cast<RTCIceGatheringState>(d->nativePeerConnection_->ice_gathering_state());
}

bool RTCPeerConnection::setConfiguration(RTCConfiguration *configuration)
{
    Q_D(RTCPeerConnection);
    d->nativePeerConnection_->SetConfiguration(*configuration->d_ptr->createNativeConfiguration());
    std::unique_ptr<webrtc::PeerConnectionInterface::RTCConfiguration> config(
        configuration->d_ptr->createNativeConfiguration());
    if (!config)
    {
        return false;
    }
    CopyConstraintsIntoRtcConfiguration(d->nativeMediaConstraints_.get(), config.get());
    return d->nativePeerConnection_->SetConfiguration(*config).ok();
}

RTCConfiguration *RTCPeerConnection::configuration()
{
    Q_D(RTCPeerConnection);
    webrtc::PeerConnectionInterface::RTCConfiguration config =
        d->nativePeerConnection_->GetConfiguration();
    return new RTCConfiguration(*(new RTCConfigurationPrivate(config)));
}

QVector<RTCRtpSender *> RTCPeerConnection::senders()
{
    Q_D(RTCPeerConnection);
    std::vector<rtc::scoped_refptr<webrtc::RtpSenderInterface>> nativeSenders(
        d->nativePeerConnection_->GetSenders());
    QVector<RTCRtpSender *> senders;
    for (const auto &nativeSender : nativeSenders)
    {
        senders.append(new RTCRtpSender(*(new RTCRtpSenderPrivate(d->factory_, nativeSender))));
    }
    return senders;
}

QVector<RTCRtpReceiver *> RTCPeerConnection::receivers()
{
    Q_D(RTCPeerConnection);
    std::vector<rtc::scoped_refptr<webrtc::RtpReceiverInterface>> nativeReceivers(
        d->nativePeerConnection_->GetReceivers());
    QVector<RTCRtpReceiver *> receivers;
    for (const auto &nativeReceiver : nativeReceivers)
    {
        receivers.append(
            new RTCRtpReceiver(*(new RTCRtpReceiverPrivate(d->factory_, nativeReceiver))));
    }
    return receivers;
}

QVector<RTCRtpTransceiver *> RTCPeerConnection::transceivers()
{
    Q_D(RTCPeerConnection);
    std::vector<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>> nativeTransceivers(
        d->nativePeerConnection_->GetTransceivers());
    QVector<RTCRtpTransceiver *> transceivers;
    for (const auto &nativeTransceiver : nativeTransceivers)
    {
        transceivers.append(
            new RTCRtpTransceiver(*(new RTCRtpTransceiverPrivate(d->factory_, nativeTransceiver))));
    }
    return transceivers;
}

void RTCPeerConnection::addIceCandidate(RTCIceCandidate *iceCandidate)
{
    Q_D(RTCPeerConnection);
    auto nativeCandidate = iceCandidate->d_ptr->nativeIceCandidate();
    d->nativePeerConnection_->AddIceCandidate(nativeCandidate.get());
}

void RTCPeerConnection::addIceCandidateWithCompletionHandler(
    RTCIceCandidate *iceCandidate, RTCIceCandidateCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);

    RTC_DCHECK(completionHandler != nullptr);

    auto nativeCandidate = iceCandidate->d_ptr->nativeIceCandidate();
    d->nativePeerConnection_->AddIceCandidate(
        std::move(nativeCandidate), [completionHandler](const auto &error) {
            if (error.ok())
            {
                completionHandler(nullptr);
            }
            else
            {
                RTCError *err = new RTCError(*(new RTCErrorPrivate(error)));
                completionHandler(err);
            }
        });
}

void RTCPeerConnection::removeIceCandidates(QVector<RTCIceCandidate *> iceCandidates)
{
    Q_D(RTCPeerConnection);

    std::vector<cricket::Candidate> candidates;
    for (RTCIceCandidate *iceCandidate : iceCandidates)
    {
        std::unique_ptr<const webrtc::IceCandidateInterface> candidate(
            iceCandidate->d_ptr->nativeIceCandidate());
        if (candidate)
        {
            candidates.push_back(candidate->candidate());
            // Need to fill the transport name from the sdp_mid.
            candidates.back().set_transport_name(candidate->sdp_mid());
        }
    }
    if (!candidates.empty())
    {
        d->nativePeerConnection()->RemoveIceCandidates(candidates);
    }
}

void RTCPeerConnection::addStream(RTCMediaStream *stream)
{
    Q_D(RTCPeerConnection);
    if (!d->nativePeerConnection_->AddStream(stream->d_ptr->nativeMediaStream().get()))
    {
        RTCLogError("Failed to add stream to peer connection %s", stream->streamId());
    }

    d->localStreams_.append(stream);
}

void RTCPeerConnection::removeStream(RTCMediaStream *stream)
{
    Q_D(RTCPeerConnection);
    d->nativePeerConnection_->RemoveStream(stream->d_ptr->nativeMediaStream().get());

    d->localStreams_.removeAll(stream);
}

RTCRtpSender *RTCPeerConnection::addTrack(RTCMediaStreamTrack *track, QVector<QString> streamIds)
{
    Q_D(RTCPeerConnection);
    std::vector<std::string> nativeStreamIds;
    for (const auto &streamId : streamIds)
    {
        nativeStreamIds.push_back(streamId.toStdString());
    }
    webrtc::RTCErrorOr<rtc::scoped_refptr<webrtc::RtpSenderInterface>> nativeSenderOrError =
        d->nativePeerConnection_->AddTrack(track->d_ptr->nativeMediaStreamTrack(), nativeStreamIds);
    if (!nativeSenderOrError.ok())
    {
        RTCLogError("Failed to add track %s: %s", track->trackId(),
                    nativeSenderOrError.error().message());
        return nullptr;
    }
    return new RTCRtpSender(
        *(new RTCRtpSenderPrivate(d->factory_, nativeSenderOrError.MoveValue())));
}

bool RTCPeerConnection::removeTrack(RTCRtpSender *sender)
{
    Q_D(RTCPeerConnection);
    bool result =
        d->nativePeerConnection_->RemoveTrackOrError(sender->d_ptr->nativeRtpSender()).ok();
    if (!result)
    {
        RTCLogError("Failed to remote track %s", sender->senderId());
    }
    return result;
}

RTCRtpTransceiver *RTCPeerConnection::addTransceiverWithTrackAndInit(RTCMediaStreamTrack *track,
                                                                     RTCRtpTransceiverInit *init)
{
    Q_D(RTCPeerConnection);
    webrtc::RTCErrorOr<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>>
        nativeTransceiverOrError = d->nativePeerConnection_->AddTransceiver(
            track->d_ptr->nativeMediaStreamTrack(), init->d_ptr->nativeRtpTransceiverInit());
    if (!nativeTransceiverOrError.ok())
    {
        RTCLogError("Failed to add transceiver: %s", nativeTransceiverOrError.error().message());
        return nullptr;
    }
    return new RTCRtpTransceiver(
        *(new RTCRtpTransceiverPrivate(d->factory_, nativeTransceiverOrError.MoveValue())));
}

RTCRtpTransceiver *RTCPeerConnection::addTransceiverWithTrack(RTCMediaStreamTrack *track)
{
    Q_D(RTCPeerConnection);
    return addTransceiverWithTrackAndInit(track, new RTCRtpTransceiverInit());
}

RTCRtpTransceiver *RTCPeerConnection::addTransceiverOfType(RTCRtpMediaType mediaType)
{
    return addTransceiverOfTypeAndInit(mediaType, new RTCRtpTransceiverInit());
}

RTCRtpTransceiver *RTCPeerConnection::addTransceiverOfTypeAndInit(RTCRtpMediaType mediaType,
                                                                  RTCRtpTransceiverInit *init)
{
    Q_D(RTCPeerConnection);
    webrtc::RTCErrorOr<rtc::scoped_refptr<webrtc::RtpTransceiverInterface>>
        nativeTransceiverOrError = d->nativePeerConnection_->AddTransceiver(
            static_cast<cricket::MediaType>(mediaType), init->d_ptr->nativeRtpTransceiverInit());
    if (!nativeTransceiverOrError.ok())
    {
        RTCLogError("Failed to add transceiver: %s", nativeTransceiverOrError.error().message());
    }
    return new RTCRtpTransceiver(
        *(new RTCRtpTransceiverPrivate(d->factory_, nativeTransceiverOrError.MoveValue())));
}

void RTCPeerConnection::restartIce()
{
    Q_D(RTCPeerConnection);
    d->nativePeerConnection_->RestartIce();
}

void RTCPeerConnection::offerForConstraints(
    RTCMediaConstraints *constraints,
    RTCCreateSessionDescriptionCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    RTC_DCHECK(completionHandler != nullptr);

    rtc::scoped_refptr<webrtc::CreateSessionDescriptionObserverAdapter> observer =
        rtc::make_ref_counted<webrtc::CreateSessionDescriptionObserverAdapter>(completionHandler);
    webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options;
    CopyConstraintsIntoOfferAnswerOptions(constraints->d_ptr->nativeMediaConstraints().get(),
                                          &options);

    d->nativePeerConnection_->CreateOffer(observer.get(), options);
}

void RTCPeerConnection::answerForConstraints(
    RTCMediaConstraints *constraints,
    RTCCreateSessionDescriptionCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    RTC_DCHECK(completionHandler != nullptr);

    rtc::scoped_refptr<webrtc::CreateSessionDescriptionObserverAdapter> observer =
        rtc::make_ref_counted<webrtc::CreateSessionDescriptionObserverAdapter>(completionHandler);
    webrtc::PeerConnectionInterface::RTCOfferAnswerOptions options;
    CopyConstraintsIntoOfferAnswerOptions(constraints->d_ptr->nativeMediaConstraints().get(),
                                          &options);

    d->nativePeerConnection_->CreateAnswer(observer.get(), options);
}

void RTCPeerConnection::setLocalDescription(
    RTCSessionDescription *sdp, RTCSetSessionDescriptionCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    RTC_DCHECK(completionHandler != nullptr);

    rtc::scoped_refptr<webrtc::SetLocalDescriptionObserverInterface> observer =
        rtc::make_ref_counted<::SetSessionDescriptionObserver>(completionHandler);
    d->nativePeerConnection_->SetLocalDescription(sdp->d_ptr->nativeSessionDescription(), observer);
}

void RTCPeerConnection::setLocalDescriptionWithCompletionHandler(
    RTCSetSessionDescriptionCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    RTC_DCHECK(completionHandler != nullptr);

    rtc::scoped_refptr<webrtc::SetLocalDescriptionObserverInterface> observer =
        rtc::make_ref_counted<::SetSessionDescriptionObserver>(completionHandler);
    d->nativePeerConnection_->SetLocalDescription(observer);
}

void RTCPeerConnection::setRemoteDescription(
    RTCSessionDescription *sdp, RTCSetSessionDescriptionCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    RTC_DCHECK(completionHandler != nullptr);

    rtc::scoped_refptr<webrtc::SetRemoteDescriptionObserverInterface> observer =
        rtc::make_ref_counted<::SetSessionDescriptionObserver>(completionHandler);
    d->nativePeerConnection_->SetRemoteDescription(sdp->d_ptr->nativeSessionDescription(),
                                                   observer);
}

bool RTCPeerConnection::setBweMinBitrateBps(QVariant minBitrateBps, QVariant currentBitrateBps,
                                            QVariant maxBitrateBps)
{
    Q_D(RTCPeerConnection);

    webrtc::BitrateSettings params;
    if (minBitrateBps.isValid())
    {
        params.min_bitrate_bps = absl::optional<int>(minBitrateBps.toInt());
    }
    if (currentBitrateBps.isValid())
    {
        params.start_bitrate_bps = absl::optional<int>(currentBitrateBps.toInt());
    }
    if (maxBitrateBps.isValid())
    {
        params.max_bitrate_bps = absl::optional<int>(maxBitrateBps.toInt());
    }
    return d->nativePeerConnection_->SetBitrate(params).ok();
}

bool RTCPeerConnection::startRtcEventLogWithFilePath(QString filePath, qint64 maxSizeInBytes)
{
    Q_D(RTCPeerConnection);

    RTC_DCHECK(filePath.size());
    RTC_DCHECK_GT(maxSizeInBytes, 0);
    RTC_DCHECK(!d->hasStartedRtcEventLog_);

    if (d->hasStartedRtcEventLog_)
    {
        RTCLogError("Event logging already started. %s", filePath);
        return false;
    }
    FILE *f = fopen(filePath.toUtf8(), "wb");
    if (!f)
    {
        RTCLogError("Error opening file: %s. Error: %d", filePath, errno);
        return false;
    }
    // TODO(eladalon): It would be better to not allow negative values into PC.
    const size_t max_size = (maxSizeInBytes < 0) ? webrtc::RtcEventLog::kUnlimitedOutput
                                                 : rtc::saturated_cast<size_t>(maxSizeInBytes);

    d->hasStartedRtcEventLog_ = d->nativePeerConnection_->StartRtcEventLog(
        std::make_unique<webrtc::RtcEventLogOutputFile>(f, max_size));
    return d->hasStartedRtcEventLog_;
}

void RTCPeerConnection::stopRtcEventLog()
{
    Q_D(RTCPeerConnection);
    d->nativePeerConnection_->StopRtcEventLog();
    d->hasStartedRtcEventLog_ = false;
}

RTCRtpSender *RTCPeerConnection::senderWithKindAndStreamId(QString kind, QString streamId)
{
    Q_D(RTCPeerConnection);
    rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeSender(
        d->nativePeerConnection_->CreateSender(kind.toStdString(), streamId.toStdString()));
    return nativeSender ? new RTCRtpSender(*(new RTCRtpSenderPrivate(d->factory_, nativeSender)))
                        : nullptr;
}

void RTCPeerConnection::close()
{
    Q_D(RTCPeerConnection);
    d->nativePeerConnection_->Close();
}

// MARK: - Data Channels

RTCDataChannel *RTCPeerConnection::dataChannelForLabelAndConfiguration(
    QString label, RTCDataChannelConfiguration *configuration)
{
    Q_D(RTCPeerConnection);
    const webrtc::DataChannelInit nativeInit = configuration->d_ptr->nativeDataChannelInit();
    auto result =
        d->nativePeerConnection_->CreateDataChannelOrError(label.toStdString(), &nativeInit);
    if (!result.ok())
    {
        return nullptr;
    }
    else
        return new RTCDataChannel(*(new RTCDataChannelPrivate(d->factory_, result.MoveValue())));
}

// MARK: - Stats

void RTCPeerConnection::statisticsForSender(RTCRtpSender *sender,
                                            RTCStatisticsCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    rtc::scoped_refptr<webrtc::StatsCollectorCallbackAdapter> collector =
        rtc::make_ref_counted<webrtc::StatsCollectorCallbackAdapter>(completionHandler);
    d->nativePeerConnection_->GetStats(sender->d_ptr->nativeRtpSender(), collector);
}

void RTCPeerConnection::statisticsForReceiver(RTCRtpReceiver *receiver,
                                              RTCStatisticsCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    rtc::scoped_refptr<webrtc::StatsCollectorCallbackAdapter> collector =
        rtc::make_ref_counted<webrtc::StatsCollectorCallbackAdapter>(completionHandler);
    d->nativePeerConnection_->GetStats(receiver->d_ptr->nativeRtpReceiver(), collector);
}

void RTCPeerConnection::statisticsWithCompletionHandler(
    RTCStatisticsCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    rtc::scoped_refptr<webrtc::StatsCollectorCallbackAdapter> collector =
        rtc::make_ref_counted<webrtc::StatsCollectorCallbackAdapter>(completionHandler);
    d->nativePeerConnection_->GetStats(collector.get());
}

void RTCPeerConnection::statsForTrack(RTCMediaStreamTrack *mediaStreamTrack,
                                      RTCStatsOutputLevel statsOutputLevel,
                                      RTCLegacyStatsReportCompletionHandler completionHandler)
{
    Q_D(RTCPeerConnection);
    rtc::scoped_refptr<webrtc::StatsObserverAdapter> observer =
        rtc::make_ref_counted<webrtc::StatsObserverAdapter>(completionHandler);
    webrtc::PeerConnectionInterface::StatsOutputLevel nativeOutputLevel =
        static_cast<webrtc::PeerConnectionInterface::StatsOutputLevel>(statsOutputLevel);
    d->nativePeerConnection_->GetStats(
        observer.get(), mediaStreamTrack->d_ptr->nativeMediaStreamTrack().get(), nativeOutputLevel);
}
