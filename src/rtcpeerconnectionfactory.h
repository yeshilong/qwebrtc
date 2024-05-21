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

#ifndef RTCPEERCONNECTIONFACTORY_H
#define RTCPEERCONNECTIONFACTORY_H

#include <QObject>

#include "rtctypes.h"

class RTCAudioSource;
class RTCAudioTrack;
class RTCConfiguration;
class RTCMediaConstraints;
class RTCMediaStream;
class RTCPeerConnection;
class RTCVideoSource;
class RTCVideoTrack;
class RTCPeerConnectionFactoryOptions;
class RTCAudioDeviceModule;
class RTCRtpCapabilities;

class IRTCPeerConnectionDelegate;
class IRTCVideoDecoderFactory;
class IRTCVideoEncoderFactory;
class IRTCSSLCertificateVerifier;
class IRTCAudioDevice;
class IRTCAudioProcessingModule;

class RTCPeerConnectionFactoryPrivate;
/**
 * @brief The RTCPeerConnectionFactory class is responsible for creating the peer connection factory.
 */
class RTCPeerConnectionFactory : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initialize object with default H264 video encoder/decoder factories and default ADM.
     */
    explicit RTCPeerConnectionFactory(QObject *parent = nullptr);

    explicit RTCPeerConnectionFactory(RTCPeerConnectionFactoryPrivate &d,
                                      QObject *parent = nullptr);

    /**
     * @brief Initialize object with injectable video encoder/decoder factories and default ADM.
     * @param encoderFactory The encoder factory.
     * @param decoderFactory The decoder factory.
     */
    explicit RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                      IRTCVideoDecoderFactory *decoderFactory,
                                      QObject *parent = nullptr);

    /**
     * @brief Initialize object with injectable video encoder/decoder factories and injectable ADM.
     * @param encoderFactory The encoder factory.
     * @param decoderFactory The decoder factory.
     * @param audioDevice The audio device.
     */
    explicit RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                      IRTCVideoDecoderFactory *decoderFactory,
                                      IRTCAudioDevice *audioDevice, QObject *parent = nullptr);

    /**
     * @brief Initialize object with bypass voice processing.
     * @param encoderFactory The encoder factory.
     * @param decoderFactory The decoder factory.
     * @param audioProcessingModule The audio processing module.
     * @param bypassVoiceProcessing Bypass voice processing.
     */
    explicit RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                      IRTCVideoDecoderFactory *decoderFactory,
                                      IRTCAudioProcessingModule *audioProcessingModule,
                                      bool bypassVoiceProcessing, QObject *parent = nullptr);

    /**
     * @brief Get the audio device module for this factory.
     * @return The audio device module.
     */
    RTCAudioDeviceModule *audioDeviceModule() const;

    /**
     * @brief Get the RTP sender capabilities for a given media type.
     * @param mediaType The media type.
     * @return The RTP capabilities.
     */
    RTCRtpCapabilities *rtpSenderCapabilitiesFor(RTCRtpMediaType mediaType);

    /**
     * @brief Get the RTP receiver capabilities for a given media type.
     * @param mediaType The media type.
     * @return The RTP capabilities.
     */
    RTCRtpCapabilities *rtpReceiverCapabilitiesFor(RTCRtpMediaType mediaType);

    /**
     * @brief Initialize an RTCAudioSource with constraints.
     * @param constraints The constraints.
     * @return The audio source.
     */
    RTCAudioSource *audioSourceWithConstraints(RTCMediaConstraints *constraints);

    /**
     * @brief Initialize an RTCAudioTrack with an id. Convenience ctor to use an audio source with no constraints.
     * @param trackId The track id.
     * @return The audio track.
     */
    RTCAudioTrack *audioTrackWithTrackId(QString trackId);

    /**
     * @brief Initialize an RTCAudioTrack with a source and an id.
     * @param source The source.
     * @param trackId The track id.
     * @return The audio track.
     */
    RTCAudioTrack *audioTrackWithSource(RTCAudioSource *source, QString trackId);

    /**
     * @brief Initialize a generic RTCVideoSource. The RTCVideoSource should be passed to a RTCVideoCapturer implementation, e.g. RTCCameraVideoCapturer, in order to produce frames.
     */
    RTCVideoSource *videoSource();

    /**
     * @brief Initialize a generic RTCVideoSource with the possibility of marking it as usable for screen sharing. The RTCVideoSource should be passed to a RTCVideoCapturer implementation, e.g. RTCCameraVideoCapturer, in order to produce frames.
     */
    RTCVideoSource *videoSourceForScreenCast(bool forScreenCast);

    /**
     * @brief Initialize an RTCVideoTrack with a source and an id.
     */
    RTCVideoTrack *videoTrackWithSource(RTCVideoSource *source, QString trackId);

    /**
     * @brief Initialize an RTCMediaStream with an id.
     */
    RTCMediaStream *mediaStreamWithStreamId(QString streamId);

    /**
     * @brief Initialize an RTCPeerConnection with a configuration, constraints, and delegate.
     */
    RTCPeerConnection *peerConnectionWithConfiguration(
        RTCConfiguration *configuration, RTCMediaConstraints *constraints,
        IRTCPeerConnectionDelegate *peerConnectionDelegate);

    /**
     * @brief Initialize an RTCPeerConnection with a configuration, constraints, certificate verifier, and delegate.
     */
    RTCPeerConnection *peerConnectionWithConfiguration(
        RTCConfiguration *configuration, RTCMediaConstraints *constraints,
        IRTCSSLCertificateVerifier *certificateVerifier,
        IRTCPeerConnectionDelegate *peerConnectionDelegate);

    /**
     * @brief Set the options to be used for subsequently created RTCPeerConnections.
     */
    void setOptions(RTCPeerConnectionFactoryOptions *options);

    /**
     * @brief Start an AecDump recording. This API call will likely change in the future.
     */
    bool startAecDumpWithFilePath(QString filePath, qint64 maxSizeInBytes);

    /**
     * @brief Stop an active AecDump recording.
     */
    void stopAecDump();

  private:
    RTCPeerConnectionFactoryPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCPeerConnectionFactory)

    bool hasStartedAecDump_ = false;

    friend class RTCMediaStreamPrivate;
    friend class RTCVideoTrackPrivate;
    friend class RTCAudioTrackPrivate;
    friend class RTCPeerConnectionPrivate;
};

#endif // RTCPEERCONNECTIONFACTORY_H
