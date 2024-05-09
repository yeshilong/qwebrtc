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
#ifndef CVIDEOTRACKSOURCE_H
#define CVIDEOTRACKSOURCE_H

#include "rtcvideocapturer.h"

#include "rtc_base/timestamp_aligner.h"
#include "media/base/adapted_video_track_source.h"

class RTCCVideoSourceAdapter;

namespace webrtc
{

class CVideoTrackSource : public rtc::AdaptedVideoTrackSource
{
  public:
    CVideoTrackSource();
    explicit CVideoTrackSource(bool is_screencast);
    explicit CVideoTrackSource(RTCCVideoSourceAdapter *adapter);

    bool is_screencast() const override;

    // Indicates that the encoder should denoise video before encoding it.
    // If it is not set, the default configuration is used which is different
    // depending on video codec.
    absl::optional<bool> needs_denoising() const override;

    SourceState state() const override;

    bool remote() const override;

    void OnCapturedFrame(RTCVideoFrame *frame);

    // Called by RTCVideoSource.
    void OnOutputFormatRequest(int width, int height, int fps);

  private:
    rtc::VideoBroadcaster broadcaster_;
    rtc::TimestampAligner timestamp_aligner_;

    RTCCVideoSourceAdapter *adapter_;
    bool is_screencast_;
};

} // namespace webrtc

class RTCCVideoSourceAdapter : IRTCVideoCapturerDelegate
{
  public:
    explicit RTCCVideoSourceAdapter(webrtc::CVideoTrackSource *cVideoTrackSource)
        : cVideoTrackSource(cVideoTrackSource)
    {
    }

    void capturer(std::shared_ptr<IRTCVideoCapturer> capturer,
                  std::shared_ptr<RTCVideoFrame> frame) override
    {
        cVideoTrackSource->OnCapturedFrame(frame.get());
    }

    webrtc::CVideoTrackSource *cVideoTrackSource;
};

#endif // CVIDEOTRACKSOURCE_H
