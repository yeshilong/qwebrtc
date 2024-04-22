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

    rtc::scoped_refptr<webrtc::MediaSourceInterface> getNativeMediaSource();

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource_;
    RTCMediaSourceType type_;
};

#endif // RTCMEDIASOURCE_P_H
