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

#include "rtcvideosource_p.h"

#include "native/objc_video_track_source.h"

#include "rtc_base/checks.h"
#include "pc/video_track_source_proxy.h"

static webrtc::ObjCVideoTrackSource *getObjCVideoSource(
    const rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> nativeSource)
{
    webrtc::VideoTrackSourceProxy *proxy_source =
        static_cast<webrtc::VideoTrackSourceProxy *>(nativeSource.get());
    return static_cast<webrtc::ObjCVideoTrackSource *>(proxy_source->internal());
}

RTCVideoSourcePrivate::RTCVideoSourcePrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> nativeVideoSource)
    : RTCMediaSourcePrivate{factory, nativeVideoSource, RTCMediaSourceType::RTCMediaSourceTypeVideo}
{
    RTC_DCHECK(factory);
    RTC_DCHECK(nativeVideoSource);
    nativeVideoSource_ = nativeVideoSource;
}

RTCVideoSourcePrivate::RTCVideoSourcePrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource)
{
    RTC_DCHECK_NOTREACHED();
}

RTCVideoSourcePrivate::RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory,
                                             rtc::Thread *signalingThread,
                                             rtc::Thread *workerThread)
{
    RTC_DCHECK(factory);
    rtc::scoped_refptr<webrtc::ObjCVideoTrackSource> objCVideoTrackSource =
        rtc::make_ref_counted<webrtc::ObjCVideoTrackSource>(false);
    nativeVideoSource_ =
        webrtc::VideoTrackSourceProxy::Create(signalingThread, workerThread, objCVideoTrackSource);
}

RTCVideoSourcePrivate::RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory,
                                             rtc::Thread *signalingThread,
                                             rtc::Thread *workerThread, bool isScreenCast)
{
    RTC_DCHECK(factory);
    rtc::scoped_refptr<webrtc::ObjCVideoTrackSource> objCVideoTrackSource =
        rtc::make_ref_counted<webrtc::ObjCVideoTrackSource>(isScreenCast);
    nativeVideoSource_ =
        webrtc::VideoTrackSourceProxy::Create(signalingThread, workerThread, objCVideoTrackSource);
}

rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> RTCVideoSourcePrivate::nativeVideoSource()
    const
{
    return nativeVideoSource_;
}

RTCVideoSource::RTCVideoSource(QObject *parent) : RTCMediaSource{parent}
{
}

RTCVideoSource::RTCVideoSource(RTCVideoSourcePrivate &d, QObject *parent)
    : RTCMediaSource{d, parent}
{
}

void RTCVideoSource::adaptOutputFormatToWidth(int width, int height, int fps)
{
    Q_D(RTCMediaSource);
    getObjCVideoSource(static_cast<RTCVideoSourcePrivate *>(d)->nativeVideoSource_)
        ->OnOutputFormatRequest(width, height, fps);
}

void RTCVideoSource::didCaptureVideoFrame(RTCVideoFrame *frame)
{
    Q_D(RTCMediaSource);
    getObjCVideoSource(static_cast<RTCVideoSourcePrivate *>(d)->nativeVideoSource_)
        ->OnCapturedFrame(frame);
}
