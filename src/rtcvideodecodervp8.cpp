#include "rtcvideodecodervp8.h"
#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/vp8/include/vp8.h"

RTCVideoDecoderVP8::RTCVideoDecoderVP8(QObject *parent) : QObject{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderVP8::vp8Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::VP8Decoder::Create())};
}
