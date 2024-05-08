#include "cvideoframe.h"
#include "cframebuffer.h"

#include "rtc_base/time_utils.h"

namespace webrtc
{

RTCVideoFrame *toCVideoFrame(const VideoFrame &frame)
{
    auto videoFrame = new RTCVideoFrame(toCVideoFrameBuffer(frame.video_frame_buffer()),
                                        RTCVideoRotation(frame.rotation()),
                                        frame.timestamp_us() * rtc::kNumNanosecsPerMicrosec);
    videoFrame->setTimeStamp(frame.timestamp());

    return videoFrame;
}

RTCVideoFrame *NativetoCVideoFrame(const VideoFrame &frame)
{
    return toCVideoFrame(frame);
}

} // namespace webrtc
