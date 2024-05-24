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

#ifndef RTCAUDIOSOURCE_P_H
#define RTCAUDIOSOURCE_P_H

#include "rtcmediasource_p.h"
#include "rtcaudiosource.h"

class RTCAudioSourcePrivate : public RTCMediaSourcePrivate
{
  public:
    RTCAudioSourcePrivate();
    RTCAudioSourcePrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::AudioSourceInterface> nativeAudioSource);
    RTCAudioSourcePrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource,
                          RTCMediaSourceType type);

    rtc::scoped_refptr<webrtc::AudioSourceInterface> nativeAudioSource();

    rtc::scoped_refptr<webrtc::AudioSourceInterface> nativeAudioSource_;
};

#endif // RTCAUDIOSOURCE_P_H
