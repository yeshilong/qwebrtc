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
