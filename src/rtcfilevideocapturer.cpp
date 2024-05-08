#include "rtcfilevideocapturer.h"

RTCFileVideoCapturer::RTCFileVideoCapturer(
    std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate, QObject *parent)
    : IRTCVideoCapturer{videoCapturerDelegate}
{
}
