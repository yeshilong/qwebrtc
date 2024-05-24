// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
