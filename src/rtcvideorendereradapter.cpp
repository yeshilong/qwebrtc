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

#include "rtcvideorendereradapter_p.h"
#include "rtcvideoframe.h"

RTCVideoRendererAdapterPrivate::RTCVideoRendererAdapterPrivate(IRTCVideoRenderer *videoRenderer)
{
    Q_ASSERT(videoRenderer);

    videoRenderer_ = videoRenderer;
    adapter_ = std::make_unique<webrtc::VideoRendererAdapter>(
        std::shared_ptr<RTCVideoRendererAdapter>(q_ptr));
}

rtc::VideoSinkInterface<webrtc::VideoFrame> *RTCVideoRendererAdapterPrivate::nativeVideoRenderer()
    const
{
    return adapter_.get();
}

RTCVideoRendererAdapter::RTCVideoRendererAdapter(IRTCVideoRenderer *videoRenderer, QObject *parent)
    : QObject(parent)
{
    d_ptr = new RTCVideoRendererAdapterPrivate(videoRenderer);
    d_ptr->q_ptr = this;
}

RTCVideoRendererAdapter::RTCVideoRendererAdapter(RTCVideoRendererAdapterPrivate &d, QObject *parent)
    : QObject(parent)
{
    d_ptr = &d;
    d_ptr->q_ptr = this;
}

IRTCVideoRenderer *RTCVideoRendererAdapter::videoRenderer() const
{
    Q_D(const RTCVideoRendererAdapter);
    return d->videoRenderer_;
}
