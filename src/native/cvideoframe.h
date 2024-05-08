#ifndef CVIDEOFRAME_H
#define CVIDEOFRAME_H

#include "rtcvideoframe.h"

#include "api/video/video_frame.h"

namespace webrtc
{

RTCVideoFrame *toCVideoFrame(const VideoFrame &frame);

} // namespace webrtc

#endif // CVIDEOFRAME_H
