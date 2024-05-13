#include "objc_video_frame.h"

#include "objc_frame_buffer.h"
#include "rtc_base/time_utils.h"

namespace webrtc {

RTCVideoFrame* ToObjCVideoFrame(const VideoFrame& frame) {
  auto videoFrame = new RTCVideoFrame(ToObjCVideoFrameBuffer(frame.video_frame_buffer()),
                                      RTCVideoRotation(frame.rotation()),
                                      frame.timestamp_us() * rtc::kNumNanosecsPerMicrosec);
  videoFrame->setTimeStamp(frame.timestamp());

  return videoFrame;
}

RTCVideoFrame* NativeToObjCVideoFrame(const VideoFrame& frame) {
  return ToObjCVideoFrame(frame);
}

}  // namespace webrtc
