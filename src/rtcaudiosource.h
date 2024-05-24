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

#ifndef RTCAUDIOSOURCE_H
#define RTCAUDIOSOURCE_H

#include <QObject>

#include "rtcmediasource.h"

class RTCAudioSourcePrivate;
/**
 * @brief Represents an audio source with a volume property.
 */
class RTCAudioSource : public RTCMediaSource
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCAudioSource class.
     */
    explicit RTCAudioSource(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCAudioSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCAudioSource(RTCAudioSourcePrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets and sets the volume for the RTCAudioSource. `volume` is a gain value in the range [0, 10].
     * Temporary fix to be able to modify volume of remote audio tracks.
     * TODO(kthelgason): Property stays here temporarily until a proper volume-api is available on the surface exposed by webrtc.
     * @return The volume.
     */
    double volume() const;
    void setVolume(double volume);

  private:
    double volume_;
};

#endif // RTCAUDIOSOURCE_H
