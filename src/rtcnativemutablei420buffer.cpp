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

#include "rtcnativemutablei420buffer.h"
#include "rtcnativemutablei420buffer_p.h"

#include "api/video/i420_buffer.h"

uint8_t *RTCMutableI420Buffer::mutableDataY() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataY();
}

uint8_t *RTCMutableI420Buffer::mutableDataU() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataU();
}

uint8_t *RTCMutableI420Buffer::mutableDataV() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataV();
}
