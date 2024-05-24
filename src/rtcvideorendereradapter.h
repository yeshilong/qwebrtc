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

#ifndef RTCVIDEORENDERERADAPTER_H
#define RTCVIDEORENDERERADAPTER_H

#include "rtcvideorenderer.h"

#include <QObject>

class RTCVideoRendererAdapterPrivate;
/**
 * @class RTCVideoRendererAdapter
 * @brief This class is an adapter that adapts calls made to the rtc::VideoSinkInterface to the IRTCVideoRenderer supplied during construction.
 */
class RTCVideoRendererAdapter : public QObject
{
    Q_OBJECT

  public:
    /**
   * @brief Construct a new RTCVideoRendererAdapter object
   * 
   * @param videoRenderer The IRTCVideoRenderer object that calls made to the rtc::VideoSinkInterface will be adapted and passed to.
   * @param parent The parent QObject.
   */
    explicit RTCVideoRendererAdapter(IRTCVideoRenderer *videoRenderer, QObject *parent = nullptr);

    /**
     * @brief Construct a new RTCVideoRendererAdapter object
     * @param d The private implementation.
     * @param parent The parent QObject.
     */
    RTCVideoRendererAdapter(RTCVideoRendererAdapterPrivate &d, QObject *parent = nullptr);

    /**
   * @brief Get the IRTCVideoRenderer object
   * 
   * @return IRTCVideoRenderer* The IRTCVideoRenderer object that calls made to the rtc::VideoSinkInterface will be adapted and passed to.
   */
    IRTCVideoRenderer *videoRenderer() const;

  private:
    RTCVideoRendererAdapterPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCVideoRendererAdapter)

    friend class RTCVideoTrack;
};

#endif // RTCVIDEORENDERERADAPTER_H
