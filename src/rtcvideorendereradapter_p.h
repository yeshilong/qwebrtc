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
#ifndef RTCVIDEORENDERERADAPTER_P_H
#define RTCVIDEORENDERERADAPTER_P_H

#include "rtcvideorendereradapter.h"

#include <memory>

#include "api/media_stream_interface.h"
#include "native/objc_video_frame.h"

namespace webrtc
{

class VideoRendererAdapter : public rtc::VideoSinkInterface<VideoFrame>
{
  public:
    explicit VideoRendererAdapter(std::shared_ptr<RTCVideoRendererAdapter> adapter)
        : adapter_(adapter), size_(0, 0)
    {
    }

    void OnFrame(const VideoFrame &nativeVideoFrame) override
    {
        RTCVideoFrame *videoFrame = NativeToObjCVideoFrame(nativeVideoFrame);

        QSize current_size = (static_cast<int>(videoFrame->rotation()) % 180 == 0)
                                 ? QSize(videoFrame->width(), videoFrame->height())
                                 : QSize(videoFrame->height(), videoFrame->width());

        auto adapter = adapter_.lock();
        if (adapter)
        {
            if (size_ != current_size)
            {
                size_ = current_size;
                adapter->videoRenderer()->setSize(size_);
            }
        }
        adapter->videoRenderer()->renderFrame(std::shared_ptr<RTCVideoFrame>(videoFrame));
    }

  private:
    std::weak_ptr<RTCVideoRendererAdapter> adapter_;
    QSize size_;
};

} // namespace webrtc

class RTCVideoRendererAdapterPrivate
{
  public:
    RTCVideoRendererAdapterPrivate(IRTCVideoRenderer *videoRenderer);
    /**
      * @brief Get the native VideoSinkInterface surface exposed by this adapter.
      * 
      * @return rtc::VideoSinkInterface<VideoFrame>* The native VideoSinkInterface surface exposed by this adapter. Calls made to this interface will be adapted and passed to the IRTCVideoRenderer supplied during construction.
      */
    rtc::VideoSinkInterface<webrtc::VideoFrame> *nativeVideoRenderer() const;

    IRTCVideoRenderer *videoRenderer_;
    rtc::VideoSinkInterface<webrtc::VideoFrame> *nativeVideoRenderer_;
    std::unique_ptr<webrtc::VideoRendererAdapter> adapter_;

    RTCVideoRendererAdapter *q_ptr;
};

#endif // RTCVIDEORENDERERADAPTER_P_H
