#include "rtccodecspecificinfoh264_p.h"

RTCCodecSpecificInfoH264Private::RTCCodecSpecificInfoH264Private()
    : packetizationMode_{RTCH264PacketizationMode::RTCH264PacketizationModeNonInterleaved}
{
}

webrtc::CodecSpecificInfo RTCCodecSpecificInfoH264Private::nativeCodecSpecificInfo() const
{
    webrtc::CodecSpecificInfo codecSpecificInfo;
    codecSpecificInfo.codecType = webrtc::kVideoCodecH264;
    codecSpecificInfo.codecSpecific.H264.packetization_mode =
        static_cast<webrtc::H264PacketizationMode>(packetizationMode_);
    return codecSpecificInfo;
}

RTCCodecSpecificInfoH264::RTCCodecSpecificInfoH264(QObject *parent)
    : IRTCCodecSpecificInfo{parent}, d_ptr{new RTCCodecSpecificInfoH264Private()}
{
}
