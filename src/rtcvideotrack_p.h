#ifndef RTCVIDEOTRACK_P_H
#define RTCVIDEOTRACK_P_H

#include <QObject>

#include "rtcvideotrack.h"
#include "rtcmediastreamtrack_p.h"
#include "rtcvideosource_p.h"
#include "rtcvideorendereradapter_p.h"

#include "rtc_base/thread.h"

class RTCVideoTrack;
class RTCVideoTrackPrivate : public RTCMediaStreamTrackPrivate
{
  public:
    explicit RTCVideoTrackPrivate(RTCPeerConnectionFactory *factory, RTCVideoSource *source,
                                  QString trackId);
    explicit RTCVideoTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeVideoTrack,
        RTCMediaStreamTrackType type);

    rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack() const;

    rtc::Thread *workerThread_;
    RTCVideoSource *source_;
    QVector<RTCVideoRendererAdapter *> adapters_;
};

#endif // RTCVIDEOTRACK_P_H
