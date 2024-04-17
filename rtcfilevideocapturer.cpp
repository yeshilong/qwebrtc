#include "rtcfilevideocapturer.h"

RTCFileVideoCapturer::RTCFileVideoCapturer(
    QSharedPointer<IRTCVideoCapturerDelegate> videoCapturerDelegate, QObject *parent)
    : RTCVideoCapturer{videoCapturerDelegate, parent}
{
}
