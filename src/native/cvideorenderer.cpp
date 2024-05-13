#include "cvideorenderer.h"

#include "cvideoframe.h"
#include "rtcvideorenderer.h"

namespace webrtc {

CVideoRenderer::CVideoRenderer(IRTCVideoRenderer* renderer) : renderer_(renderer), size_(QSize()) {}

void CVideoRenderer::OnFrame(const webrtc::VideoFrame& nativeVideoFrame) {
  RTCVideoFrame* videoFrame = toCVideoFrame(nativeVideoFrame);

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
