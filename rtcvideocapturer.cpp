#include "rtcvideocapturer.h"

RTCVideoCapturer::RTCVideoCapturer(QSharedPointer<IRTCVideoCapturerDelegate> videoCapturerDelegate,
                                   QObject *parent)
    : QObject{parent}
{
}
