#include "rtcdesktopcapturer.h"

RTCDesktopCapturer::RTCDesktopCapturer(
    QSharedPointer<RTCDesktopSource> desktopSource,
    QSharedPointer<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
    QSharedPointer<IRTCVideoCapturerDelegate> captureDelegate, QObject *parent)
    : RTCVideoCapturer{captureDelegate, parent}
{
}
RTCDesktopCapturer::RTCDesktopCapturer(
    QSharedPointer<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
    QSharedPointer<IRTCVideoCapturerDelegate> captureDelegate, QObject *parent)
    : RTCVideoCapturer{captureDelegate, parent}
{
}
