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

#ifndef RTCPEERCONNECTION_H
#define RTCPEERCONNECTION_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "rtctypes.h"

class IRTCPeerConnectionDelegate;
class RTCConfiguration;
class RTCDataChannel;
class RTCDataChannelConfiguration;
class RTCError;
class RTCIceCandidate;
class RTCIceCandidateErrorEvent;
class RTCLegacyStatsReport;
class RTCMediaConstraints;
class RTCMediaStream;
class RTCMediaStreamTrack;
class RTCPeerConnectionFactory;
class RTCRtpReceiver;
class RTCRtpSender;
class RTCRtpTransceiver;
class RTCRtpTransceiverInit;
class RTCSessionDescription;
class RTCStatisticsReport;

/**
 * @brief Represents the completion handler for creating a session description.
 */
using RTCCreateSessionDescriptionCompletionHandler =
    std::function<void(RTCSessionDescription *sdp, RTCError *error)>;

/**
 * @brief Represents the completion handler for setting a session description.
 */
using RTCSetSessionDescriptionCompletionHandler = std::function<void(RTCError *error)>;

/**
 * @brief Represents the completion handler for adding an ICE candidate.
 */
using RTCIceCandidateCompletionHandler = std::function<void(RTCError *error)>;
using RTCStatisticsCompletionHandler = std::function<void(std::shared_ptr<RTCStatisticsReport>)>;
using RTCLegacyStatsReportCompletionHandler =
    std::function<void(std::vector<std::shared_ptr<RTCLegacyStatsReport>>)>;

namespace webrtc
{

class PeerConnectionDelegateAdapter;

} // namespace webrtc
class RTCPeerConnectionPrivate;
/**
 * @brief The RTCPeerConnection class represents a peer connection.
 */
class RTCPeerConnection : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCPeerConnection object.
     * @param parent The parent object.
     */
    explicit RTCPeerConnection(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCPeerConnection object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCPeerConnection(RTCPeerConnectionPrivate &d, QObject *parent = nullptr);

    /**
     * @brief The object that will be notified about events such as state changes and streams being added or removed.
     */
    IRTCPeerConnectionDelegate *delegate();

    /**
     * @brief This property is not available with RTCSdpSemanticsUnifiedPlan. Please use `Senders` instead.
     */
    QVector<RTCMediaStream *> localStreams();

    /**
     * @brief The local session description.
     */
    RTCSessionDescription *localDescription();

    /**
     * @brief The remote session description.
     */
    RTCSessionDescription *remoteDescription();

    /**
     * @brief The signaling state.
     */
    RTCSignalingState signalingState();

    /**
     * @brief The ICE connection state.
     */
    RTCIceConnectionState iceConnectionState();

    /**
     * @brief The connection state.
     */
    RTCPeerConnectionState connectionState();

    /**
     * @brief The ICE gathering state.
     */
    RTCIceGatheringState iceGatheringState();

    /**
     * @brief The configuration.
     */
    RTCConfiguration *configuration();

    /**
     * @brief Gets all RTCRtpSenders associated with this peer connection.
     * Note: reading this property returns different instances of RTCRtpSender.
     * Use isEqual: instead of == to compare RTCRtpSender instances.
     */
    QVector<RTCRtpSender *> senders();

    /**
     * @brief Gets all RTCRtpReceivers associated with this peer connection.
     * Note: reading this property returns different instances of RTCRtpReceiver.
     * Use isEqual: instead of == to compare RTCRtpReceiver instances.
     */
    QVector<RTCRtpReceiver *> receivers();

    /**
     * @brief Gets all RTCRtpTransceivers associated with this peer connection.
     * Note: reading this property returns different instances of RTCRtpTransceiver.
     * Use isEqual: instead of == to compare RTCRtpTransceiver instances.
     * This is only available with RTCSdpSemanticsUnifiedPlan specified.
     */
    QVector<RTCRtpTransceiver *> transceivers();

    /**
     * @brief Sets the PeerConnection's global configuration to `configuration`.
     * Any changes to STUN/TURN servers or ICE candidate policy will affect the
     * next gathering phase, and cause the next call to createOffer to generate
     * new ICE credentials. Note that the BUNDLE and RTCP-multiplexing policies
     * cannot be changed with this method.
     */
    bool setConfiguration(RTCConfiguration *configuration);

    /**
     * @brief Terminate all media and close the transport.
     */
    void close();

    /**
     * @brief Provide a remote candidate to the ICE Agent.
     * This method is deprecated. Use addIceCandidateWithCompletionHandler instead.
     */
    Q_DECL_DEPRECATED void addIceCandidate(RTCIceCandidate *iceCandidate);

    /**
     * @brief Provide a remote candidate to the ICE Agent.
     */
    void addIceCandidateWithCompletionHandler(RTCIceCandidate *iceCandidate,
                                              RTCIceCandidateCompletionHandler completionHandler);

    /**
     * @brief Remove a group of remote candidates from the ICE Agent.
     */
    void removeIceCandidates(QVector<RTCIceCandidate *> iceCandidates);

    /**
     * @brief Add a new media stream to be sent on this peer connection.
     * This method is not supported with RTCSdpSemanticsUnifiedPlan. Please use
     * addTrack instead.std::shared_ptr<qint64>
     */
    void addStream(RTCMediaStream *stream);

    /**
     * @brief Remove the given media stream from this peer connection.
     * This method is not supported with RTCSdpSemanticsUnifiedPlan. Please use
     * removeTrack instead.
     */
    void removeStream(RTCMediaStream *stream);

    /**
     * @brief Add a new media stream track to be sent on this peer connection, and return
     * the newly created RTCRtpSender. The RTCRtpSender will be
     * associated with the streams specified in the `streamIds` list.
     *
     * Errors: If an error occurs, returns null. An error can occur if:
     * - A sender already exists for the track.
     * - The peer connection is closed.
     */
    RTCRtpSender *addTrack(RTCMediaStreamTrack *track, QVector<QString> streamIds);

    /**
     * @brief With PlanB semantics, removes an RTCRtpSender from this peer connection.
     * With UnifiedPlan semantics, sets sender's track to null and removes the
     * send component from the associated RTCRtpTransceiver's direction.
     * Returns true on success.
     */
    bool removeTrack(RTCRtpSender *sender);

    /**
     * @brief AddTransceiver creates a new RTCRtpTransceiver and adds it to the set of
     * transceivers. Adding a transceiver will cause future calls to CreateOffer
     * to add a media description for the corresponding transceiver.
     * The initial value of `mid` in the returned transceiver is null. Setting a
     * new session description may change it to a non-nil value.
     * Optionally, an RtpTransceiverInit structure can be specified to configure
     * the transceiver from construction. If not specified, the transceiver will
     * default to having a direction of kSendRecv and not be part of any streams.
     * These methods are only available when Unified Plan is enabled (see
     * RTCConfiguration).
     */
    RTCRtpTransceiver *addTransceiverWithTrack(RTCMediaStreamTrack *track);
    RTCRtpTransceiver *addTransceiverWithTrackAndInit(RTCMediaStreamTrack *track,
                                                      RTCRtpTransceiverInit *init);

    /**
     * @brief Adds a transceiver with the given kind. Can either be RTCRtpMediaTypeAudio
     * or RTCRtpMediaTypeVideo.
     */
    RTCRtpTransceiver *addTransceiverOfType(RTCRtpMediaType mediaType);
    RTCRtpTransceiver *addTransceiverOfTypeAndInit(RTCRtpMediaType mediaType,
                                                   RTCRtpTransceiverInit *init);

    /**
     * @brief Tells the PeerConnection that ICE should be restarted. This triggers a need
     * for negotiation and subsequent OfferForConstraints call will act as if
     * RTCOfferAnswerOptions::ice_restart is true.
     */
    void restartIce();

    /**
     * @brief Generate an SDP offer.
     */
    void offerForConstraints(RTCMediaConstraints *constraints,
                             RTCCreateSessionDescriptionCompletionHandler completionHandler);

    /**
     * @brief Generate an SDP answer.
     */
    void answerForConstraints(RTCMediaConstraints *constraints,
                              RTCCreateSessionDescriptionCompletionHandler completionHandler);

    /**
     * @brief Apply the supplied RTCSessionDescription as the local description.
     */
    void setLocalDescription(RTCSessionDescription *sdp,
                             RTCSetSessionDescriptionCompletionHandler completionHandler);

    /**
     * @brief Creates an offer or answer (depending on current signaling state) and sets
     * it as the local session description.
     */
    void setLocalDescriptionWithCompletionHandler(
        RTCSetSessionDescriptionCompletionHandler completionHandler);

    /**
     * @brief Apply the supplied RTCSessionDescription as the remote description.
     */
    void setRemoteDescription(RTCSessionDescription *sdp,
                              RTCSetSessionDescriptionCompletionHandler completionHandler);

    /**
     * @brief Limits the bandwidth allocated for all RTP streams sent by this PeerConnection. Nil parameters will be unchanged. Setting `currentBitrateBps` will force the available bitrate estimate to the given value. Returns true if the parameters were successfully updated.
     */
    bool setBweMinBitrateBps(QVariant minBitrateBps, QVariant currentBitrateBps,
                             QVariant maxBitrateBps);

    /**
     * @brief Start or stop recording an Rtc EventLog.
     */
    bool startRtcEventLogWithFilePath(QString filePath, qint64 maxSizeInBytes);
    void stopRtcEventLog();

    /**
     * @brief Create an RTCRtpSender with the specified kind and media stream ID. See RTCMediaStreamTrack.h for available kinds. This method is not supported with RTCSdpSemanticsUnifiedPlan. Please use addTransceiver instead.
     */
    RTCRtpSender *senderWithKindAndStreamId(QString kind, QString streamId);

    /**
     * @brief Create a new data channel with the given label and configuration.
     */
    RTCDataChannel *dataChannelForLabelAndConfiguration(QString label,
                                                        RTCDataChannelConfiguration *configuration);

    /**
     * @brief Gather stats for the given RTCMediaStreamTrack. If `mediaStreamTrack` is null statistics are gathered for all tracks.
     */
    void statsForTrack(RTCMediaStreamTrack *mediaStreamTrack, RTCStatsOutputLevel statsOutputLevel,
                       RTCLegacyStatsReportCompletionHandler completionHandler);

    /**
     * @brief Gather statistic through the v2 statistics API.
     */
    void statisticsWithCompletionHandler(RTCStatisticsCompletionHandler completionHandler);

    /**
     * @brief Spec-compliant getStats() performing the stats selection algorithm with the sender.
     */
    void statisticsForSender(RTCRtpSender *sender,
                             RTCStatisticsCompletionHandler completionHandler);

    /**
     * @brief Spec-compliant getStats() performing the stats selection algorithm with the receiver.
     */
    void statisticsForReceiver(RTCRtpReceiver *receiver,
                               RTCStatisticsCompletionHandler completionHandler);

  private:
    RTCPeerConnectionPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCPeerConnection)

    friend class webrtc::PeerConnectionDelegateAdapter;
};

#endif // RTCPEERCONNECTION_H
