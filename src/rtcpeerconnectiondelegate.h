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

#ifndef RTCPEERCONNECTIONDELEGATE_H
#define RTCPEERCONNECTIONDELEGATE_H

#include <QObject>

#include "rtctypes.h"

class RTCPeerConnection;
class RTCRtpTransceiver;
class RTCRtpReceiver;
class RTCMediaStream;
class RTCIceCandidate;
class RTCIceCandidateErrorEvent;
class RTCDataChannel;

/**
 * @brief The IRTCPeerConnectionDelegate class.
 */
class IRTCPeerConnectionDelegate : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Called when the SignalingState changed.
     * @param peerConnection The peer connection.
     * @param stateChanged The state that changed.
     */
    virtual void didChangeSignalingState(RTCPeerConnection *peerConnection,
                                         RTCSignalingState stateChanged) = 0;

    /**
     * @brief Called when media is received on a new stream from remote peer.
     * @param peerConnection The peer connection.
     * @param stream The stream.
     */
    virtual void didAddStream(RTCPeerConnection *peerConnection, RTCMediaStream *stream) = 0;

    /**
     * @brief Called when a remote peer closes a stream.
     * @param peerConnection The peer connection.
     * @param stream The stream.
     */
    virtual void didRemoveStream(RTCPeerConnection *peerConnection, RTCMediaStream *stream) = 0;

    /**
     * @brief Called when negotiation is needed, for example ICE has restarted.
     * @param peerConnection The peer connection.
     */
    virtual void peerConnectionShouldNegotiate(RTCPeerConnection *peerConnection) = 0;

    /**
     * @brief Called any time the IceConnectionState changes.
     * @param peerConnection The peer connection.
     * @param newState The new state.
     */
    virtual void didChangeIceConnectionState(RTCPeerConnection *peerConnection,
                                             RTCIceConnectionState newState) = 0;

    /**
     * @brief Called any time the IceGatheringState changes.
     * @param peerConnection The peer connection.
     * @param newState The new state.
     */
    virtual void didChangeIceGatheringState(RTCPeerConnection *peerConnection,
                                            RTCIceGatheringState newState) = 0;

    /**
     * @brief New ice candidate has been found.
     * @param peerConnection The peer connection.
     * @param candidate The candidate.
     */
    virtual void didGenerateIceCandidate(RTCPeerConnection *peerConnection,
                                         RTCIceCandidate *candidate) = 0;

    /**
     * @brief Called when a group of local Ice candidates have been removed.
     * @param peerConnection The peer connection.
     * @param candidates The candidates.
     */
    virtual void didRemoveIceCandidates(RTCPeerConnection *peerConnection,
                                        QVector<RTCIceCandidate *> candidates) = 0;

    /**
     * @brief New data channel has been opened.
     * @param peerConnection The peer connection.
     * @param dataChannel The data channel.
     */
    virtual void didOpenDataChannel(RTCPeerConnection *peerConnection,
                                    RTCDataChannel *dataChannel) = 0;

    /**
     * @brief Called when signaling indicates a transceiver will be receiving media from the remote endpoint.
     * @param peerConnection The peer connection.
     * @param transceiver The transceiver.
     */
    virtual void didStartReceivingOnTransceiver(RTCPeerConnection *peerConnection,
                                                RTCRtpTransceiver *transceiver) = 0;

    /**
     * @brief Called any time the IceConnectionState changes following standardized transition.
     * @param peerConnection The peer connection.
     * @param newState The new state.
     */
    virtual void didChangeStandardizedIceConnectionState(RTCPeerConnection *peerConnection,
                                                         RTCIceConnectionState newState) = 0;

    /**
     * @brief Called any time the PeerConnectionState changes.
     * @param peerConnection The peer connection.
     * @param newState The new state.
     */
    virtual void didChangeConnectionState(RTCPeerConnection *peerConnection,
                                          RTCPeerConnectionState newState) = 0;

    /**
     * @brief Called when a receiver and its track are created.
     * @param peerConnection The peer connection.
     * @param rtpReceiver The RTP receiver.
     * @param mediaStreams The media streams.
     */
    virtual void didAddReceiver(RTCPeerConnection *peerConnection, RTCRtpReceiver *rtpReceiver,
                                QVector<RTCMediaStream *> mediaStreams) = 0;

    /**
     * @brief Called when the receiver and its track are removed.
     * @param peerConnection The peer connection.
     * @param rtpReceiver The RTP receiver.
     */
    virtual void didRemoveReceiver(RTCPeerConnection *peerConnection,
                                   RTCRtpReceiver *rtpReceiver) = 0;

    /**
     * @brief Called when the selected ICE candidate pair is changed.
     * @param peerConnection The peer connection.
     * @param localCandidate The local candidate.
     * @param remoteCandidate The remote candidate.
     * @param lastDataReceivedMs The last data received in milliseconds.
     * @param reason The reason.
     */
    virtual void didChangeLocalCandidate(RTCPeerConnection *peerConnection,
                                         RTCIceCandidate *localCandidate,
                                         RTCIceCandidate *remoteCandidate, int lastDataReceivedMs,
                                         QString reason) = 0;

    /**
     * @brief Called when gathering of an ICE candidate failed.
     * @param peerConnection The peer connection.
     * @param candidateErrorEvent The candidate error event.
     */
    virtual void didFailToGatherIceCandidate(RTCPeerConnection *peerConnection,
                                             RTCIceCandidateErrorEvent *candidateErrorEvent) = 0;
};

#endif // RTCPEERCONNECTIONDELEGATE_H
