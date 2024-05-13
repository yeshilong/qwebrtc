/*
 * Copyright 2022 LiveKit
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "objc_desktop_capture.h"

#include <QTime>
#include <QVideoFrame>

#include "api/sequence_checker.h"
#include "objc_desktop_capture.h"
#include "objc_video_frame.h"
#include "rtc_base/checks.h"
#include "rtcdesktopcapturer_p.h"
#include "rtcqimagebuffer.h"
#include "third_party/libyuv/include/libyuv.h"

namespace webrtc {

enum { kCaptureDelay = 33, kCaptureMessageId = 1000 };

ObjCDesktopCapturer::ObjCDesktopCapturer(DesktopType type,
                                         webrtc::DesktopCapturer::SourceId source_id,
                                         CDesktopCapturerDelegate* delegate)
    : thread_(rtc::Thread::Create()), source_id_(source_id), delegate_(delegate) {
  RTC_DCHECK(thread_);
  type_ = type;
  thread_->Start();
  options_ = webrtc::DesktopCaptureOptions::CreateDefault();
  options_.set_detect_updated_region(true);
#if defined(WEBRTC_MAC) && !defined(WEBRTC_IOS)
  options_.set_allow_iosurface(true);
#endif  // defined(WEBRTC_MAC) && !defined(WEBRTC_IOS)
  thread_->BlockingCall([this, type] {
    if (type == kScreen) {
      capturer_ = std::make_unique<DesktopAndCursorComposer>(
          webrtc::DesktopCapturer::CreateScreenCapturer(options_), options_);
    } else {
      capturer_ = std::make_unique<DesktopAndCursorComposer>(
          webrtc::DesktopCapturer::CreateWindowCapturer(options_), options_);
    }
  });
}

ObjCDesktopCapturer::~ObjCDesktopCapturer() {
  thread_->BlockingCall([this] { capturer_.reset(); });
}

ObjCDesktopCapturer::CaptureState ObjCDesktopCapturer::Start(uint32_t fps) {
  if (capture_state_ == CS_RUNNING) {
    return capture_state_;
  }

  if (fps == 0) {
    capture_state_ = CS_FAILED;
    return capture_state_;
  }

  if (fps >= 60) {
    capture_delay_ = uint32_t(1000.0 / 60.0);
  } else {
    capture_delay_ = uint32_t(1000.0 / fps);
  }

  if (source_id_ != -1) {
    if (!capturer_->SelectSource(source_id_)) {
      capture_state_ = CS_FAILED;
      return capture_state_;
    }
    if (type_ == kWindow) {
      if (!capturer_->FocusOnSelectedSource()) {
        capture_state_ = CS_FAILED;
        return capture_state_;
      }
    }
  }

  thread_->BlockingCall([this] { capturer_->Start(this); });
  capture_state_ = CS_RUNNING;

  thread_->PostTask([this] { CaptureFrame(); });

  delegate_->didSourceCaptureStart();
  return capture_state_;
}

void ObjCDesktopCapturer::Stop() {
  delegate_->didSourceCaptureStop();
  capture_state_ = CS_STOPPED;
}

bool ObjCDesktopCapturer::IsRunning() {
  return capture_state_ == CS_RUNNING;
}

void ObjCDesktopCapturer::OnCaptureResult(webrtc::DesktopCapturer::Result result,
                                          std::unique_ptr<webrtc::DesktopFrame> frame) {
  if (result != result_) {
    if (result == webrtc::DesktopCapturer::Result::ERROR_PERMANENT) {
      delegate_->didSourceCaptureError();
      capture_state_ = CS_FAILED;
      return;
    }

    if (result == webrtc::DesktopCapturer::Result::ERROR_TEMPORARY) {
      result_ = result;
      delegate_->didSourceCapturePause();
      return;
    }

    if (result == webrtc::DesktopCapturer::Result::SUCCESS) {
      result_ = result;
      delegate_->didSourceCaptureStart();
    }
  }

  if (result == webrtc::DesktopCapturer::Result::ERROR_TEMPORARY) {
    return;
  }

  int width = frame->size().width();
  int height = frame->size().height();
  int real_width = width;

  if (type_ == kWindow) {
    int multiple = 0;
#if defined(WEBRTC_ARCH_X86_FAMILY)
    multiple = 16;
#elif defined(WEBRTC_ARCH_ARM64)
    multiple = 32;
#endif
    // A multiple of $multiple must be used as the width of the src frame,
    // and the right black border needs to be cropped during conversion.
    if (multiple != 0 && (width % multiple) != 0) {
      width = (width / multiple + 1) * multiple;
    }
  }

  QImage image(frame->size().width(), frame->size().height(), QImage::Format_ARGB32);

  uchar* pxdata = image.bits();

  libyuv::ConvertToARGB(reinterpret_cast<uint8_t*>(frame->data()),
                        real_width * height * 4,
                        reinterpret_cast<uint8_t*>(pxdata),
                        width * 4,
                        0,
                        0,
                        width,
                        height,
                        real_width,
                        height,
                        libyuv::kRotate0,
                        libyuv::FOURCC_ARGB);

  if (image.isNull()) {
    qDebug() << "Unable to create QImage";
    return;
  }

  qint64 timeStampNs = QDateTime::currentDateTime().toMSecsSinceEpoch() * 1000000;

  std::shared_ptr<RTCVideoFrame> videoFrame = std::make_shared<RTCVideoFrame>(
      std::make_shared<RTCQImageBuffer>(image), RTCVideoRotation::RTCVideoRotation_0, timeStampNs);

  delegate_->didCaptureFrame(videoFrame);

  delete[] pxdata;
}

void ObjCDesktopCapturer::CaptureFrame() {
  RTC_DCHECK_RUN_ON(thread_.get());
  if (capture_state_ == CS_RUNNING) {
    capturer_->CaptureFrame();
    thread_->PostDelayedHighPrecisionTask([this]() { CaptureFrame(); },
                                          TimeDelta::Millis(capture_delay_));
  }
}

}  // namespace webrtc
