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

#ifndef RTCMEDIASOURCE_P_H
#define RTCMEDIASOURCE_P_H

#include "api/media_stream_interface.h"

#include "rtctypes.h"

class RTCPeerConnectionFactory;

class RTCMediaSourcePrivate
{
  public:
    RTCMediaSourcePrivate();
    RTCMediaSourcePrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource,
                          RTCMediaSourceType type);

    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource();

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource_;
    RTCMediaSourceType type_;
};

#endif // RTCMEDIASOURCE_P_H
