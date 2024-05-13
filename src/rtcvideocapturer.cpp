#include "rtcvideocapturer.h"

IRTCVideoCapturer::IRTCVideoCapturer(
    std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate)
{
    delegate_ = videoCapturerDelegate;
}

std::shared_ptr<IRTCVideoCapturerDelegate> IRTCVideoCapturer::delegate() const
{
    return delegate_;
}

void IRTCVideoCapturer::setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate)
{
    delegate_ = delegate;
}
