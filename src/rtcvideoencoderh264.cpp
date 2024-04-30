#include "rtcvideoencoderh264.h"
#include "rtcwrappednativevideoencoder.h"

#include "modules/video_coding/codecs/h264/include/h264.h"

RTCVideoEncoderH264::RTCVideoEncoderH264(RTCVideoCodecInfo *codecInfo, QObject *parent)
    : IRTCVideoEncoder{parent}
{
}

// IRTCVideoEncoder *RTCVideoEncoderH264::h264Encoder()
// {
//     return new RTCWrappedNativeVideoEncoder{
//         std::unique_ptr<webrtc::VideoEncoder>(webrtc::H264Encoder::Create())};
// }
