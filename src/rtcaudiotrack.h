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

#ifndef RTCAUDIOTRACK_H
#define RTCAUDIOTRACK_H

#include <QObject>

#include "rtcaudiorenderer.h"
#include "rtcaudiosource.h"
#include "rtcmediastreamtrack.h"

class RTCAudioTrackPrivate;
/**
 * @brief Represents an audio track with a source and methods to add and remove renderers.
 */
class RTCAudioTrack : public RTCMediaStreamTrack
{
    Q_OBJECT

  public:
    /**
     * @brief Creates a new instance.
     * @param parent The parent object.
     */
    explicit RTCAudioTrack(RTCAudioTrackPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Returns the audio source for this audio track.
     * @return The audio source.
     */
    RTCAudioSource *source();

    /**
     * @brief Registers a renderer that will receive all audio sample buffers on this track.
     * @param renderer The renderer.
     */
    void addRenderer(IRTCAudioRenderer *renderer);

    /**
     * @brief Deregisters a renderer.
     * @param renderer The renderer.
     */
    void removeRenderer(IRTCAudioRenderer *renderer);

    /**
     * @brief called when a new sample buffer is captured.
     * @return The audio sample buffer.
     */
    void didCaptureSampleBuffer(QAudioBuffer sampleBuffer);
};

#endif // RTCAUDIOTRACK_H
