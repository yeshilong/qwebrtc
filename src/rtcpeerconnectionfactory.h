#ifndef RTCPEERCONNECTIONFACTORY_H
#define RTCPEERCONNECTIONFACTORY_H

#include <QObject>

#include "rtctypes.h"

class IRTCVideoEncoderFactory;
class IRTCVideoDecoderFactory;
class IRTCAudioDevice;
class IRTCAudioProcessingModule;
class RTCAudioDeviceModule;
class RTCRtpCapabilities;
class RTCAudioSource;
class RTCMediaConstraints;
class RTCAudioTrack;
class RTCVideoSource;
class RTCVideoTrack;
class RTCMediaStream;
class RTCConfiguration;
class RTCMediaConstraints;
class IRTCPeerConnectionDelegate;
class IRTCSSLCertificateVerifier;
class RTCPeerConnection;
class RTCPeerConnectionFactoryOptions;

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
     * @param bypassVoiceProcessing Bypass voice processing.
     * @param encoderFactory The encoder factory.
     * @param decoderFactory The decoder factory.
     * @param audioProcessingModule The audio processing module.
     */
    explicit RTCPeerConnectionFactory(bool bypassVoiceProcessing,
                                      IRTCVideoEncoderFactory *encoderFactory,
                                      IRTCVideoDecoderFactory *decoderFactory,
                                      IRTCAudioProcessingModule *audioProcessingModule,
                                      QObject *parent = nullptr);

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
    RTCRtpCapabilities *rtpSenderCapabilitiesFor(RTCRtpMediaType *mediaType);

    /**
     * @brief Get the RTP receiver capabilities for a given media type.
     * @param mediaType The media type.
     * @return The RTP capabilities.
     */
    RTCRtpCapabilities *rtpReceiverCapabilitiesFor(RTCRtpMediaType *mediaType);

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
};

#endif // RTCPEERCONNECTIONFACTORY_H