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

#ifndef RTCVIDEORENDERER_H
#define RTCVIDEORENDERER_H

#include <QObject>
#include <QSize>

class RTCVideoFrame;

/**
 * @brief The IRTCVideoRenderer interface.
 */
class IRTCVideoRenderer
{
  public:
    virtual void setSize(const QSize &size) = 0;
    virtual void renderFrame(std::shared_ptr<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The IRTCVideoViewDelegate interface.
 */
class IRTCVideoViewDelegate
{
  public:
    virtual void videoView(std::shared_ptr<IRTCVideoRenderer> videoView, const QSize &size) = 0;
};

#endif // RTCVIDEORENDERER_H
