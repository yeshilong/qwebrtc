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

#include "rtcaudiosource.h"
#include "rtcaudiosource_p.h"

#include "rtc_base/checks.h"

RTCAudioSourcePrivate::RTCAudioSourcePrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::AudioSourceInterface> nativeAudioSource)
    : RTCMediaSourcePrivate(factory, nativeAudioSource, RTCMediaSourceType::RTCMediaSourceTypeAudio)
{
    RTC_DCHECK(factory);
    RTC_DCHECK(nativeAudioSource);
    nativeAudioSource_ = nativeAudioSource;
}

RTCAudioSourcePrivate::RTCAudioSourcePrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource, RTCMediaSourceType type)
{
    RTC_DCHECK_NOTREACHED();
}

rtc::scoped_refptr<webrtc::AudioSourceInterface> RTCAudioSourcePrivate::nativeAudioSource()
{
    return nativeAudioSource_;
}

RTCAudioSource::RTCAudioSource(QObject *parent) : RTCMediaSource{parent}
{
}

RTCAudioSource::RTCAudioSource(RTCAudioSourcePrivate &d, QObject *parent)
    : RTCMediaSource{d, parent}
{
}

double RTCAudioSource::volume() const
{
    return volume_;
}

void RTCAudioSource::setVolume(double volume)
{
    volume_ = volume;
    ((RTCAudioSourcePrivate *)d_ptr)->nativeAudioSource_->SetVolume(volume);
}
