#include "rtcvideotrack.h"
#include "rtcvideotrack_p.h"

RTCVideoTrack::RTCVideoTrack(RTCVideoTrackPrivate &d, QObject *parent)
    : RTCMediaStreamTrack{d, parent}
{
}
