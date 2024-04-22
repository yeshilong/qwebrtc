#ifndef RTCVIDEOTRACK_P_H
#define RTCVIDEOTRACK_P_H

#include <QObject>

#include "rtcmediastreamtrack_p.h"

class RTCVideoTrack;

class RTCVideoTrackPrivate : public RTCMediaStreamTrackPrivate
{
  public:
    explicit RTCVideoTrackPrivate(
        const rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack,
        RTCPeerConnectionFactory *factory);
    RTCVideoTrackPrivate(const rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack,
                         RTCPeerConnectionFactory *factory, RTCMediaStreamTrackType type);

    rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack() const;
    bool isEqualToTrack(RTCVideoTrackPrivate *other) const;
    static RTCVideoTrack *videoTrackForNativeVideoTrack(
        const rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack,
        RTCPeerConnectionFactory *factory);

    rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack_;
};

#endif // RTCVIDEOTRACK_P_H
