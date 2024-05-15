#ifndef RTCMEDIASTREAMTRACK_P_H
#define RTCMEDIASTREAMTRACK_P_H

#include <QObject>

#include "rtctypes.h"

#include "api/media_stream_interface.h"

class RTCPeerConnectionFactory;
class RTCMediaStreamTrack;

class RTCMediaStreamTrackPrivate
{
  public:
    /**
     * @brief RTCMediaStreamTrackPrivate
     * @param nativeMediaStreamTrack The native media stream track.
     * @param factory The peer connection factory.
     * @param type The type of the media stream track.
     */
    explicit RTCMediaStreamTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
        RTCMediaStreamTrackType type);

    /**
     * @brief RTCMediaStreamTrackPrivate
     * @param nativeMediaStreamTrack The native media stream track.
     * @param factory The peer connection factory.
     */
    RTCMediaStreamTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack);

    /**
     * @brief Returns the native media stream track.
     * @return The native media stream track.
     */
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack() const;

    /**
     * @brief Checks if the media stream track is equal to another media stream track.
     * @return True if the media stream track is equal to the other media stream track, false otherwise.
     */
    bool isEqualToTrack(RTCMediaStreamTrackPrivate *other) const;

    /**
     * @brief Creates a media stream track for a native media stream track.
     * @return The media stream track.
     */
    static RTCMediaStreamTrack *mediaStreamTrackForNativeMediaStreamTrack(
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
        RTCPeerConnectionFactory *factory);

    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack_;
    RTCPeerConnectionFactory *factory_;
    RTCMediaStreamTrackType type_;
};

#endif // RTCMEDIASTREAMTRACK_P_H
