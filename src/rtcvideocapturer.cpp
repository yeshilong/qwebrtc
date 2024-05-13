#include "rtcvideocapturer.h"

RTCVideoCapturer::RTCVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate)
{
    delegate_ = videoCapturerDelegate;
}

std::shared_ptr<IRTCVideoCapturerDelegate> RTCVideoCapturer::delegate() const
{
    return delegate_;
}

void RTCVideoCapturer::setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate)
{
    delegate_ = delegate;
}
