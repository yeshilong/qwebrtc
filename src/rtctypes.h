#ifndef RTCTYPES_H
#define RTCTYPES_H

/**
 * @brief Enumeration to represent distinct classes of errors that an
 * application may wish to act upon differently. These roughly map to
 * DOMExceptions or RTCError "errorDetailEnum" values in the web API,
 * as described in the comments below.
 */
enum class RTCErrorType
{
    /**
     * @brief No error.
     */
    None,
    /**
     * @brief An operation is valid, but currently unsupported. Maps to
     * OperationError DOMException.
     */
    UnsupportedOperation,
    /**
     * @brief A supplied parameter is valid, but currently unsupported. Maps
     * to OperationError DOMException.
     */
    UnsupportedParameter,
    /**
     * @brief General error indicating that a supplied parameter is invalid.
     * Maps to InvalidAccessError or TypeError DOMException depending
     * on context.
     */
    InvalidParameter,
    /**
     * @brief Slightly more specific than invalidParameter; a parameter's
     * value was outside the allowed range. Maps to RangeError
     * DOMException.
     */
    InvalidRange,
    /**
     * @brief Slightly more specific than invalidParameter; an error occurred
     * while parsing string input. Maps to SyntaxError DOMException.
     */
    SyntaxError,
    /**
     * @brief The object does not support this operation in its current state.
     * Maps to InvalidStateError DOMException.
     */
    InvalidState,
    /**
     * @brief An attempt was made to modify the object in an invalid way. Maps
     * to InvalidModificationError DOMException.
     */
    InvalidModification,
    /**
     * @brief An error occurred within an underlying network protocol. Maps to
     * NetworkError DOMException.
     */
    NetworkError,
    /**
     * @brief Some resource has been exhausted; file handles, hardware
     * resources, ports, etc. Maps to OperationError DOMException.
     */
    ResourceExhausted,
    /**
     * @brief The operation failed due to an internal error. Maps to
     * OperationError DOMException.
     */
    InternalError,
    /**
     * @brief   // An error occured that has additional data.
     * The additional data is specified in
     * https://w3c.github.io/webrtc-pc/#rtcerror-interface
     * Maps to RTCError DOMException.
     */
    OperationErrorWithData
};

// Detail information, showing what further information should be present.
// https://w3c.github.io/webrtc-pc/#rtcerrordetailtype-enum
enum class RTCErrorDetailType
{
    None,
    DataChannelFailure,
    DtlsFailure,
    FingerprintFailure,
    SctpFailure,
    SdpSyntaxError,
    HardwareEncoderNotAvailable,
    HardwareEncoderError
};

/**
 * @brief Represents the severity levels for file logging.
 */
enum class RTCFileLoggerSeverity
{
    Verbose,
    Info,
    Warning,
    Error
};

/**
 * @brief Represents the rotation types for file logging.
 */
enum class RTCFileLoggerRotationType
{
    Call,
    App,
};

/**
 * @brief Subset of rtc::LoggingSeverity.
 */
enum class RTCLoggingSeverity
{
    Verbose,
    Info,
    Warning,
    Error,
    None,
};

/**
 * @brief Video rotation options.
 */
enum class RTCVideoRotation
{
    RTCVideoRotation_0 = 0,
    RTCVideoRotation_90 = 90,
    RTCVideoRotation_180 = 180,
    RTCVideoRotation_270 = 270
};

/**
 * @brief The RTCMediaStreamTrackState enum represents the state of an RTCMediaStreamTrack.
 */
enum class RTCMediaStreamTrackState
{
    Live,
    Ended,
};

/**
 * @brief Represents the ice transport policy.
 */
enum class RTCIceTransportPolicy
{
    RTCIceTransportPolicyNone,
    RTCIceTransportPolicyRelay,
    RTCIceTransportPolicyNoHost,
    RTCIceTransportPolicyAll
};

/**
 * @brief Represents the bundle policy.
 */
enum class RTCBundlePolicy
{
    RTCBundlePolicyBalanced,
    RTCBundlePolicyMaxCompat,
    RTCBundlePolicyMaxBundle
};

/**
 * @brief Represents the rtcp mux policy.
 */
enum class RTCRtcpMuxPolicy
{
    RTCRtcpMuxPolicyNegotiate,
    RTCRtcpMuxPolicyRequire
};

/**
 * @brief Represents the tcp candidate policy.
 */
enum class RTCTcpCandidatePolicy
{
    RTCTcpCandidatePolicyEnabled,
    RTCTcpCandidatePolicyDisabled
};

/**
 * @brief Represents the candidate network policy.
 */
enum class RTCCandidateNetworkPolicy
{
    RTCCandidateNetworkPolicyAll,
    RTCCandidateNetworkPolicyLowCost
};

/**
 * @brief Represents the continual gathering policy.
 */
enum class RTCContinualGatheringPolicy
{
    RTCContinualGatheringPolicyGatherOnce,
    RTCContinualGatheringPolicyGatherContinually
};

/**
 * @brief Represents the encryption key type.
 */
enum class RTCEncryptionKeyType
{
    RTCEncryptionKeyTypeRSA,
    RTCEncryptionKeyTypeECDSA
};

/**
 * @brief Represents the chosen SDP semantics for the RTCPeerConnection.
 */
enum class RTCSdpSemantics
{
    RTCSdpSemanticsPlanB,
    RTCSdpSemanticsUnifiedPlan
};

/**
 * @brief The RTCTlsCertPolicy indicates the TLS certificate policy
 */
enum class RTCTlsCertPolicy
{
    /// @brief For TLS based protocols, ensure the connection is secure by not
    /// circumventing certificate validation.
    TlsCertPolicySecure,
    /// @brief For TLS based protocols, disregard security completely by
    /// skipping certificate validation. This is insecure and should
    /// never be used unless security is irrelevant in that particular
    /// context.
    TlsCertPolicyInsecureNoCheck
};

/**
 * @brief Represents the signaling state of the peer connection.
 */
enum class RTCSignalingState
{
    Stable,
    HaveLocalOffer,
    HaveLocalPrAnswer,
    HaveRemoteOffer,
    HaveRemotePrAnswer,
    Closed,
};

/**
 * @brief Represents the ice connection state of the peer connection.
 */
enum class RTCIceConnectionState
{
    New,
    Checking,
    Connected,
    Completed,
    Failed,
    Disconnected,
    Closed,
    Count,
};

/**
 * @brief Represents the combined ice+dtls connection state of the peer connection.
 */
enum class RTCPeerConnectionState
{
    New,
    Connecting,
    Connected,
    Disconnected,
    Failed,
    Closed,
};

/**
 * @brief Represents the ice gathering state of the peer connection.
 */
enum class RTCIceGatheringState
{
    New,
    Gathering,
    Complete,
};

/**
 * @brief Represents the stats output level.
 */
enum class RTCStatsOutputLevel
{
    Standard,
    Debug,
};

/**
 * @brief The RTCIODeviceType enum represents the type of an RTCIODevice.
 */
enum class RTCIODeviceType
{
    RTCIODeviceTypeOutput,
    RTCIODeviceTypeInput,
};

/**
 * @brief Represents a video codec mode.
 */
enum class RTCVideoCodecMode
{
    RTCVideoCodecModeRealtimeVideo,
    RTCVideoCodecModeScreensharing,
};

/**
 * @brief Represents an encoded frame's type.
 */
enum class RTCFrameType
{
    RTCFrameTypeEmptyFrame = 0,
    RTCFrameTypeAudioFrameSpeech = 1,
    RTCFrameTypeAudioFrameCN = 2,
    RTCFrameTypeVideoFrameKey = 3,
    RTCFrameTypeVideoFrameDelta = 4
};

/**
 * @brief Represents a video content's type.
 */
enum class RTCVideoContentType
{
    RTCVideoContentTypeUnspecified,
    RTCVideoContentTypeScreenshare,
};

/**
 * @brief Represents the session description type.
 */
enum class RTCSdpType
{
    RTCSdpTypeOffer,
    RTCSdpTypePrAnswer,
    RTCSdpTypeAnswer,
    RTCSdpTypeRollback,
};

/**
 * @brief Represents the direction of the RTCRtpTransceiver.
 */
enum class RTCRtpTransceiverDirection
{
    RTCRtpTransceiverDirectionSendRecv,
    RTCRtpTransceiverDirectionSendOnly,
    RTCRtpTransceiverDirectionRecvOnly,
    RTCRtpTransceiverDirectionInactive,
    RTCRtpTransceiverDirectionStopped
};

/**
 * @brief Represents the media type of the RtpReceiver.
 */
enum class RTCRtpMediaType
{
    RTCRtpMediaTypeAudio,
    RTCRtpMediaTypeVideo,
    RTCRtpMediaTypeData,
    RTCRtpMediaTypeUnsupported,
};

/**
 * @brief Corresponds to webrtc::DegradationPreference.
 */
enum class RTCDegradationPreference
{
    RTCDegradationPreferenceDisabled,
    RTCDegradationPreferenceMaintainFramerate,
    RTCDegradationPreferenceMaintainResolution,
    RTCDegradationPreferenceBalanced
};

/**
 * @brief Corresponds to webrtc::Priority.
 */
enum class RTCPriority
{
    RTCPriorityVeryLow,
    RTCPriorityLow,
    RTCPriorityMedium,
    RTCPriorityHigh
};

/**
 * @brief Enum for RTCCyrptorAlgorithm.
 */
enum class RTCCyrptorAlgorithm
{
    AesGcm = 0,
    AesCbc = 1
};

/**
 * @brief Enum for FrameCryptionState.
 */
enum class RTCFrameCryptionState
{
    New = 0,
    Ok = 1,
    EncryptionFailed = 2,
    DecryptionFailed = 3,
    MissingKey = 4,
    KeyRatcheted = 5,
    InternalError = 6
};

/**
 * @brief Enum for RTCDispatcherQueueType.
 */
enum class RTCDispatcherQueueType
{
    RTCDispatcherTypeMain,
    RTCDispatcherTypeCaptureSession,
    RTCDispatcherTypeAudioSession,
    RTCDispatcherTypeNetworkMonitor
};

/**
 * @brief Enum representing the type of desktop source.
 */
enum class RTCDesktopSourceType
{
    Screen,
    Window,
};

/**
 * @brief The RTCH264PacketizationMode enum represents the packetization mode for H264 codec.
 */
enum class RTCH264PacketizationMode
{
    RTCH264PacketizationModeNonInterleaved = 0,
    RTCH264PacketizationModeSingleNalUnit = 1
};

/**
 * @brief H264 Profiles.
 */
enum class RTCH264Profile
{
    ConstrainedBaseline,
    Baseline,
    Main,
    ConstrainedHigh,
    High
};

/**
 * @brief H264 Levels.
 */
enum class RTCH264Level
{
    Level1_b = 0,
    Level1 = 10,
    Level1_1 = 11,
    Level1_2 = 12,
    Level1_3 = 13,
    Level2 = 20,
    Level2_1 = 21,
    Level2_2 = 22,
    Level3 = 30,
    Level3_1 = 31,
    Level3_2 = 32,
    Level4 = 40,
    Level4_1 = 41,
    Level4_2 = 42,
    Level5 = 50,
    Level5_1 = 51,
    Level5_2 = 52
};

/**
 * @brief Enumerates the possible states of an RTC media source.
 */
enum class RTCSourceState
{
    Initializing,
    Live,
    Ended,
    Muted,
};

/**
 * @brief Enumerates the possible states of a data channel.
 */
enum class RTCDataChannelState
{
    RTCDataChannelStateConnecting,
    RTCDataChannelStateOpen,
    RTCDataChannelStateClosing,
    RTCDataChannelStateClosed,
};

/**
 * @brief Enumerates the possible types media sources.
 */
enum class RTCMediaSourceType
{
    RTCMediaSourceTypeAudio,
    RTCMediaSourceTypeVideo,
};

/**
 * @brief Enumerates the possible types media stream tracks.
 */
enum class RTCMediaStreamTrackType
{
    RTCMediaStreamTrackTypeAudio,
    RTCMediaStreamTrackTypeVideo,
};

#endif // RTCTYPES_H
