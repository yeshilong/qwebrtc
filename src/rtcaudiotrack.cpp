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

#include "rtcaudiotrack_p.h"

#include <mutex>

RTCAudioTrackPrivate::RTCAudioTrackPrivate(RTCPeerConnectionFactory *factory,
                                           RTCAudioSource *source, QString trackId)
    : RTCMediaStreamTrackPrivate(
          factory,
          factory->d_ptr->nativePeerConnectionFactory()->CreateAudioTrack(
              trackId.toStdString(),
              static_cast<RTCAudioSourcePrivate *>(source->d_ptr)->nativeAudioSource().get()),
          RTCMediaStreamTrackType::RTCMediaStreamTrackTypeAudio)
{
    Q_ASSERT(factory);
    Q_ASSERT(source);
    Q_ASSERT(!trackId.isEmpty());
    source_ = source;
}

RTCAudioTrackPrivate::RTCAudioTrackPrivate(
    RTCPeerConnectionFactory *factory,
    const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeAudioTrack,
    RTCMediaStreamTrackType type)
    : RTCMediaStreamTrackPrivate{factory, nativeAudioTrack, type}
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeAudioTrack);
    Q_ASSERT(type == RTCMediaStreamTrackType::RTCMediaStreamTrackTypeAudio);
    audioSinkConverter_ = new rtc::RefCountedObject<webrtc::AudioSinkConverter>(
        std::shared_ptr<RTCAudioTrackPrivate>(this), &lock_);
}

RTCAudioTrackPrivate::~RTCAudioTrackPrivate()
{
    std::lock_guard<std::mutex> lock(lock_);
    audioSinkConverter_->TryDetach();
    RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate dealloc";
}

rtc::scoped_refptr<webrtc::AudioTrackInterface> RTCAudioTrackPrivate::nativeAudioTrack() const
{
    return rtc::scoped_refptr<webrtc::AudioTrackInterface>(
        static_cast<webrtc::AudioTrackInterface *>(this->nativeMediaStreamTrack().get()));
}

RTCAudioTrack::RTCAudioTrack(RTCAudioTrackPrivate &d, QObject *parent)
    : RTCMediaStreamTrack{d, parent}
{
    d.q_ptr = this;
}

RTCAudioSource *RTCAudioTrack::source()
{
    Q_D(RTCMediaStreamTrack);
    RTCAudioTrackPrivate *q = static_cast<RTCAudioTrackPrivate *>(d);
    if (!q->source_)
    {
        rtc::scoped_refptr<webrtc::AudioSourceInterface> source(q->nativeAudioTrack()->GetSource());
        if (source)
        {
            q->source_ = new RTCAudioSource(*(new RTCAudioSourcePrivate(q->factory_, source)));
        }
    }
    return q->source_;
}

void RTCAudioTrack::addRenderer(IRTCAudioRenderer *renderer)
{
    Q_D(RTCMediaStreamTrack);
    RTCAudioTrackPrivate *q = static_cast<RTCAudioTrackPrivate *>(d);
    std::lock_guard<std::mutex> lock(q->lock_);
    q->renderers_.insert(renderer);
    q->audioSinkConverter_->TryAttach();
}

void RTCAudioTrack::removeRenderer(IRTCAudioRenderer *renderer)
{
    Q_D(RTCMediaStreamTrack);
    RTCAudioTrackPrivate *q = static_cast<RTCAudioTrackPrivate *>(d);
    std::lock_guard<std::mutex> lock(q->lock_);
    q->renderers_.remove(renderer);
    if (q->renderers_.empty())
    {
        q->audioSinkConverter_->TryDetach();
    }
}

void RTCAudioTrack::didCaptureSampleBuffer(QAudioBuffer sampleBuffer)
{
    Q_D(RTCMediaStreamTrack);
    RTCAudioTrackPrivate *q = static_cast<RTCAudioTrackPrivate *>(d);

    std::unique_lock<std::mutex> lock(q->lock_, std::try_to_lock);
    if (!lock.owns_lock())
    {
        RTC_LOG(LS_INFO) << "RTCAudioTrack didCaptureSampleBuffer already locked, skipping...";
        return;
    }
    for (IRTCAudioRenderer *renderer : q->renderers_)
    {
        renderer->render(sampleBuffer);
    }
}
