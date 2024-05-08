#include "rtcdesktopcapturer.h"

RTCDesktopCapturer::RTCDesktopCapturer(
    std::shared_ptr<RTCDesktopSource> desktopSource,
    std::shared_ptr<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
    std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate, QObject *parent)
    : IRTCVideoCapturer{captureDelegate}
{
}
RTCDesktopCapturer::RTCDesktopCapturer(
    std::shared_ptr<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
    std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate, QObject *parent)
    : IRTCVideoCapturer{captureDelegate}
{
}
