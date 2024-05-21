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
