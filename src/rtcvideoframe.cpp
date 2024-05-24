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

#include "rtcvideoframe.h"

#include "rtcvideoframebuffer.h"

RTCVideoFrame::RTCVideoFrame(std::shared_ptr<IRTCVideoFrameBuffer> frameBuffer,
                             RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    buffer_ = frameBuffer;
    rotation_ = rotation;
    timeStampNs_ = timeStampNs;
}

RTCVideoFrame::RTCVideoFrame(QImage *pixelBuffer, RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    // Deprecated.
}

RTCVideoFrame::RTCVideoFrame(QImage *pixelBuffer, const QSize &scaledSize, const QRect &cropRect,
                             RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    // Deprecated.
}

int RTCVideoFrame::width() const
{
    return buffer_->width();
}

int RTCVideoFrame::height() const
{
    return buffer_->height();
}

RTCVideoRotation RTCVideoFrame::rotation() const
{
    return rotation_;
}

qint64 RTCVideoFrame::timeStampNs() const
{
    return timeStampNs_;
}

int RTCVideoFrame::timeStamp() const
{
    return timeStamp_;
}

void RTCVideoFrame::setTimeStamp(int timeStamp)
{
    timeStamp_ = timeStamp;
}

std::shared_ptr<IRTCVideoFrameBuffer> RTCVideoFrame::buffer() const
{
    return buffer_;
}
