#ifndef CVIDEOFRAME_H
#define CVIDEOFRAME_H

#include "api/video/video_frame.h"
#include "rtcvideoframe.h"

namespace webrtc {

RTCVideoFrame* ToObjCVideoFrame(const VideoFrame& frame);

}  // namespace webrtc

#endif  // CVIDEOFRAME_H
