#include "rtcvideodecoderav1.h"

#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/av1/dav1d_decoder.h"

RTCVideoDecoderAV1::RTCVideoDecoderAV1(QObject *parent) : QObject{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderAV1::av1Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::CreateDav1dDecoder())};
}
