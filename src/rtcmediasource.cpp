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

#include "rtcmediasource.h"
#include "rtcmediasource_p.h"

RTCMediaSourcePrivate::RTCMediaSourcePrivate()
{
}

RTCMediaSourcePrivate::RTCMediaSourcePrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource, RTCMediaSourceType type)
{
    RTC_DCHECK(factory);
    RTC_DCHECK(nativeMediaSource);
    factory_ = factory;
    nativeMediaSource_ = nativeMediaSource;
    type_ = type;
}

rtc::scoped_refptr<webrtc::MediaSourceInterface> RTCMediaSourcePrivate::nativeMediaSource()
{
    return nativeMediaSource_;
}

RTCMediaSource::RTCMediaSource(QObject *parent)
    : QObject{parent}, d_ptr{new RTCMediaSourcePrivate{}}
{
}

RTCMediaSource::RTCMediaSource(RTCMediaSourcePrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

RTCSourceState RTCMediaSource::state() const
{
    Q_D(const RTCMediaSource);
    return static_cast<RTCSourceState>(d->nativeMediaSource_->state());
}
