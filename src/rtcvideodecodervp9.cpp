#include "rtcvideodecodervp9.h"
#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/vp9/include/vp9.h"

RTCVideoDecoderVP9::RTCVideoDecoderVP9(QObject *parent) : QObject{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderVP9::vp9Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::VP9Decoder::Create())};
}

bool RTCVideoDecoderVP9::isSupported()
{
#if defined(RTC_ENABLE_VP9)
    return true;
#else
    return false;
#endif
}
