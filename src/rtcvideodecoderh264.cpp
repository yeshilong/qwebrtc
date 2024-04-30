#include "rtcvideodecoderh264.h"
#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/h264/include/h264.h"

RTCVideoDecoderH264::RTCVideoDecoderH264(QObject *parent) : IRTCVideoDecoder{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderH264::h264Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::H264Decoder::Create())};
}

bool RTCVideoDecoderH264::isSupported()
{
    return webrtc::H264Decoder::IsSupported();
}
