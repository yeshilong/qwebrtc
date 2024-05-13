#ifndef CVIDEORENDERER_H
#define CVIDEORENDERER_H

#ifndef SDK_CPP_NATIVE_SRC_CPP_VIDEO_RENDERER_H_
#define SDK_CPP_NATIVE_SRC_CPP_VIDEO_RENDERER_H_

#include <QSize>

#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"

class IRTCVideoRenderer;

namespace webrtc {

class CVideoRenderer : public rtc::VideoSinkInterface<VideoFrame> {
 public:
  CVideoRenderer(IRTCVideoRenderer* renderer);
  void OnFrame(const VideoFrame& nativeVideoFrame) override;

 private:
  IRTCVideoRenderer* renderer_;
  QSize size_;
};

}  // namespace webrtc

#endif  // SDK_CPP_NATIVE_SRC_CPP_VIDEO_RENDERER_H_

#endif  // CVIDEORENDERER_H
