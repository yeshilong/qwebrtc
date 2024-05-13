#include "objc_video_renderer.h"

#include "objc_video_frame.h"
#include "rtcvideorenderer.h"

namespace webrtc {

ObjCVideoRenderer::ObjCVideoRenderer(IRTCVideoRenderer* renderer)
    : renderer_(renderer), size_(QSize()) {}

void ObjCVideoRenderer::OnFrame(const webrtc::VideoFrame& nativeVideoFrame) {
  RTCVideoFrame* videoFrame = ToObjCVideoFrame(nativeVideoFrame);

  QSize current_size = (static_cast<int>(videoFrame->rotation()) % 180 == 0) ?
      QSize(videoFrame->width(), videoFrame->height()) :
      QSize(videoFrame->height(), videoFrame->width());

  if (size_ != current_size) {
    size_ = current_size;
    renderer_->setSize(size_);
  }
  renderer_->renderFrame(std::shared_ptr<RTCVideoFrame>(videoFrame));
}

}  // namespace webrtc
