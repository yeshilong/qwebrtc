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

#include "rtcaudiobuffer_p.h"

RTCAudioBufferPrivate::RTCAudioBufferPrivate(webrtc::AudioBuffer *audioBuffer)
    : audioBuffer_{audioBuffer}
{
}

RTCAudioBufferPrivate::~RTCAudioBufferPrivate()
{
}

webrtc::AudioBuffer *RTCAudioBufferPrivate::audioBuffer() const
{
    return audioBuffer_;
}

RTCAudioBuffer::RTCAudioBuffer(QObject *parent)
    : QObject{parent}, d_ptr{new RTCAudioBufferPrivate{nullptr}}
{
}

RTCAudioBuffer::RTCAudioBuffer(RTCAudioBufferPrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
}

unsigned int RTCAudioBuffer::channels() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_channels();
}

unsigned int RTCAudioBuffer::frames() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_frames();
}

unsigned int RTCAudioBuffer::framesPerBand() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_frames_per_band();
}

unsigned int RTCAudioBuffer::bands() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_bands();
}
