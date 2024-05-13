/*
 * Copyright (C) 2024 Deltarion Systems
 *
 * This software is licensed under the terms of the GNU Lesser
 * General Public License (LGPL) version 3 as published by the Free
 * Software Foundation. This license is available at:
 * https://www.gnu.org/licenses/lgpl-3.0.html
 *
 * You are free to modify and distribute this software under the
 * terms of the LGPLv3 license. You are required to make the source
 * code of any modifications available under the same license.
 */
#include "objc_video_track_source.h"

#include "api/video/i420_buffer.h"
#include "objc_frame_buffer.h"
#include "rtcqimagebuffer.h"
#include "rtcvideoframe.h"
#include "rtcvideoframebuffer.h"

namespace webrtc {

ObjCVideoTrackSource::ObjCVideoTrackSource() : ObjCVideoTrackSource(false) {}

ObjCVideoTrackSource::ObjCVideoTrackSource(bool is_screencast)
    : AdaptedVideoTrackSource(/* required resolution alignment */ 2),
      is_screencast_(is_screencast) {}

ObjCVideoTrackSource::ObjCVideoTrackSource(RTCCVideoSourceAdapter* adapter) : adapter_(adapter) {
  adapter_->objCVideoTrackSource = this;
}

bool ObjCVideoTrackSource::is_screencast() const {
  return is_screencast_;
}

absl::optional<bool> ObjCVideoTrackSource::needs_denoising() const {
  return false;
}

MediaSourceInterface::SourceState ObjCVideoTrackSource::state() const {
  return SourceState::kLive;
}

bool ObjCVideoTrackSource::remote() const {
  return false;
}

void ObjCVideoTrackSource::OnOutputFormatRequest(int width, int height, int fps) {
  cricket::VideoFormat format(width, height, cricket::VideoFormat::FpsToInterval(fps), 0);
  video_adapter()->OnOutputFormatRequest(format);
}

void ObjCVideoTrackSource::OnCapturedFrame(RTCVideoFrame* frame) {
  const int64_t timestamp_us = frame->timeStampNs() / rtc::kNumNanosecsPerMicrosec;
  const int64_t translated_timestamp_us =
      timestamp_aligner_.TranslateTimestamp(timestamp_us, rtc::TimeMicros());

  int adapted_width;
  int adapted_height;
  int crop_width;
  int crop_height;
  int crop_x;
  int crop_y;
  if (!AdaptFrame(frame->width(),
                  frame->height(),
                  timestamp_us,
                  &adapted_width,
                  &adapted_height,
                  &crop_width,
                  &crop_height,
                  &crop_x,
                  &crop_y)) {
    return;
  }

  rtc::scoped_refptr<VideoFrameBuffer> buffer;
  if (adapted_width == frame->width() && adapted_height == frame->height()) {
    // No adaption - optimized path.
    buffer = rtc::make_ref_counted<ObjCFrameBuffer>(frame->buffer().get());
  } else if (dynamic_cast<RTCQImageBuffer*>(frame->buffer().get())) {
    // Adapted QVideoFrameBuffer frame.
    RTCQImageBuffer* rtcPixelBuffer = dynamic_cast<RTCQImageBuffer*>(frame->buffer().get());
    buffer = rtc::make_ref_counted<ObjCFrameBuffer>(
        new RTCQImageBuffer(rtcPixelBuffer->pixelBuffer(),
                            adapted_width,
                            adapted_height,
                            crop_width,
                            crop_height,
                            crop_x + rtcPixelBuffer->cropX(),
                            crop_y + rtcPixelBuffer->cropY()));
  } else {
    // Adapted I420 frame.
    // TODO(magjed): Optimize this I420 path.
    rtc::scoped_refptr<I420Buffer> i420_buffer = I420Buffer::Create(adapted_width, adapted_height);
    buffer = rtc::make_ref_counted<ObjCFrameBuffer>(frame->buffer().get());
    i420_buffer->CropAndScaleFrom(*buffer->ToI420(), crop_x, crop_y, crop_width, crop_height);
    buffer = i420_buffer;
  }

  // Applying rotation is only supported for legacy reasons and performance is
  // not critical here.
  VideoRotation rotation = static_cast<VideoRotation>(frame->rotation());
  if (apply_rotation() && rotation != kVideoRotation_0) {
    buffer = I420Buffer::Rotate(*buffer->ToI420(), rotation);
    rotation = kVideoRotation_0;
  }

  OnFrame(VideoFrame::Builder()
              .set_video_frame_buffer(buffer)
              .set_rotation(rotation)
              .set_timestamp_us(translated_timestamp_us)
              .build());
}

}  // namespace webrtc
