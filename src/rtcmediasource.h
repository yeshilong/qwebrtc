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

#ifndef RTCMEDIASOURCE_H
#define RTCMEDIASOURCE_H

#include <QObject>

#include "rtctypes.h"

class RTCMediaSourcePrivate;

/**
 * @brief Represents a media source used for capturing and transmitting audio or video.
 */
class RTCMediaSource : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     */
    explicit RTCMediaSource(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCMediaSource(RTCMediaSourcePrivate &d, QObject *parent = nullptr);

    /**
     * @brief Returns the current state of the RTCMediaSource.
     * @return The current state.
     */
    RTCSourceState state() const;

  protected:
    RTCMediaSourcePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaSource)

    friend class RTCVideoTrackPrivate;
    friend class RTCAudioTrackPrivate;
};

#endif // RTCMEDIASOURCE_H
