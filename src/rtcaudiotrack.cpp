#include "rtcaudiotrack.h"
#include "rtcaudiotrack_p.h"

RTCAudioTrack::RTCAudioTrack(RTCAudioTrackPrivate &d, QObject *parent)
    : RTCMediaStreamTrack{d, parent}
{
}
