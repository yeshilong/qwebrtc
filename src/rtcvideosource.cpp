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
    getObjCVideoSource(((RTCVideoSourcePrivate *)d)->nativeVideoSource_)
        ->OnOutputFormatRequest(width, height, fps);
}

void RTCVideoSource::didCaptureVideoFrame(RTCVideoFrame *frame)
{
    Q_D(RTCMediaSource);
    getObjCVideoSource(((RTCVideoSourcePrivate *)d)->nativeVideoSource_)->OnCapturedFrame(frame);
}
