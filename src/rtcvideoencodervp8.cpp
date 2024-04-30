#include "rtcvideoencodervp8.h"
#include "rtcwrappednativevideoencoder.h"

#include "modules/video_coding/codecs/vp8/include/vp8.h"

RTCVideoEncoderVP8::RTCVideoEncoderVP8(QObject *parent) : QObject{parent}
{
}

IRTCVideoEncoder *RTCVideoEncoderVP8::vp8Encoder()
{
    return new RTCWrappedNativeVideoEncoder{webrtc::VP8Encoder::Create()};
}
