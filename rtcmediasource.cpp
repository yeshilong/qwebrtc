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

rtc::scoped_refptr<webrtc::MediaSourceInterface> RTCMediaSourcePrivate::getNativeMediaSource()
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
    return static_cast<RTCSourceState>(d_ptr->nativeMediaSource_->state());
}
