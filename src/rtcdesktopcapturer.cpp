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

#include "rtcdesktopcapturer_p.h"
#include "rtcdesktopsource_p.h"
#include "rtcvideoframe.h"

RTCDesktopCapturer::RTCDesktopCapturer(std::shared_ptr<RTCDesktopSource> desktopSource,
                                       std::shared_ptr<IRTCDesktopCapturerDelegate> delegate,
                                       std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                       QObject *parent)
    : RTCVideoCapturer{captureDelegate}
{
    webrtc::DesktopType captureType = webrtc::kScreen;
    if (desktopSource->sourceType() == RTCDesktopSourceType::Window)
    {
        captureType = webrtc::kWindow;
    }

    d_ptr->nativeDesktopCapturer_ = std::make_shared<webrtc::ObjCDesktopCapturer>(
        captureType, desktopSource->d_ptr->nativeMediaSource_->id(), this);

    desktopSource_ = desktopSource;
    delegate_ = delegate;
}
RTCDesktopCapturer::RTCDesktopCapturer(std::shared_ptr<IRTCDesktopCapturerDelegate> delegate,
                                       std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                       QObject *parent)
    : RTCVideoCapturer{captureDelegate}
{
    d_ptr->nativeDesktopCapturer_ =
        std::make_shared<webrtc::ObjCDesktopCapturer>(webrtc::kScreen, -1, this);
    desktopSource_ = nullptr;
    delegate_ = delegate;
}

RTCDesktopCapturer::~RTCDesktopCapturer()
{
    Q_D(RTCDesktopCapturer);
    d->nativeDesktopCapturer_->Stop();
    d->nativeDesktopCapturer_ = nullptr;
}

std::shared_ptr<RTCDesktopSource> RTCDesktopCapturer::source() const
{
    return desktopSource_;
}

void RTCDesktopCapturer::startCapture()
{
    this->delegate_->didSourceCaptureStart(std::shared_ptr<RTCDesktopCapturer>(this));
    Q_D(RTCDesktopCapturer);
    d->nativeDesktopCapturer_->Start(30);
}

void RTCDesktopCapturer::startCaptureWithFPS(int fps)
{
    this->delegate_->didSourceCaptureStart(std::shared_ptr<RTCDesktopCapturer>(this));
    Q_D(RTCDesktopCapturer);
    d->nativeDesktopCapturer_->Start(fps);
}

void RTCDesktopCapturer::stopCapture()
{
    Q_D(RTCDesktopCapturer);
    d->nativeDesktopCapturer_->Stop();
    this->delegate_->didSourceCaptureStop(std::shared_ptr<RTCDesktopCapturer>(this));
}

void RTCDesktopCapturer::stopCaptureWithCompletionHandler(std::function<void()> completionHandler)
{
    Q_D(RTCDesktopCapturer);
    d->nativeDesktopCapturer_->Stop();
    completionHandler();
    this->delegate_->didSourceCaptureStop(std::shared_ptr<RTCDesktopCapturer>(this));
}

void RTCDesktopCapturer::didCaptureFrame(const std::shared_ptr<RTCVideoFrame> frame)
{
    this->delegate()->capturer(std::shared_ptr<RTCDesktopCapturer>(this), frame);
}

void RTCDesktopCapturer::didSourceCaptureStart()
{
    this->delegate_->didSourceCaptureStart(std::shared_ptr<RTCDesktopCapturer>(this));
}

void RTCDesktopCapturer::didSourceCapturePause()
{
    this->delegate_->didSourceCapturePaused(std::shared_ptr<RTCDesktopCapturer>(this));
}

void RTCDesktopCapturer::didSourceCaptureStop()
{
    this->delegate_->didSourceCaptureStop(std::shared_ptr<RTCDesktopCapturer>(this));
}

void RTCDesktopCapturer::didSourceCaptureError()
{
    this->delegate_->didSourceCaptureError(std::shared_ptr<RTCDesktopCapturer>(this));
}
