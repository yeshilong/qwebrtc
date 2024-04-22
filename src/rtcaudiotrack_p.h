#ifndef RTCAUDIOTRACK_P_H
#define RTCAUDIOTRACK_P_H

#include <QObject>

#include "rtcmediastreamtrack_p.h"

class RTCAudioTrack;

class RTCAudioTrackPrivate : public RTCMediaStreamTrackPrivate
{
  public:
    explicit RTCAudioTrackPrivate(
        const rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack,
        RTCPeerConnectionFactory *factory);
    RTCAudioTrackPrivate(const rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack,
                         RTCPeerConnectionFactory *factory, RTCMediaStreamTrackType type);

    rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack() const;
    bool isEqualToTrack(RTCAudioTrackPrivate *other) const;
    static RTCAudioTrack *audioTrackForNativeAudioTrack(
        const rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack,
        RTCPeerConnectionFactory *factory);

    rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack_;
};

#endif // RTCAUDIOTRACK_P_H
