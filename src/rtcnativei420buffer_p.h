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

#ifndef RTCNATIVEI420BUFFER_P_H
#define RTCNATIVEI420BUFFER_P_H

#include "rtcnativei420buffer.h"

#include "api/video/i420_buffer.h"

class RTCI420BufferPrivate
{
  public:
    RTCI420BufferPrivate();
    RTCI420BufferPrivate(rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer);

    rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer() const;

    rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer_;
};

#endif // RTCNATIVEI420BUFFER_P_H
