#ifndef RTCDESKTOPCAPTURER_H
#define RTCDESKTOPCAPTURER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include "rtcdesktopsource.h"
#include "rtcvideocapturer.h"

class RTCDesktopCapturer;

/**
 * @brief The IRTCDesktopCapturerDelegate class.
 */
class IRTCDesktopCapturerDelegate
{
  public:
    virtual void didSourceCaptureStart(QSharedPointer<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCapturePaused(QSharedPointer<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCaptureStop(QSharedPointer<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCaptureError(QSharedPointer<RTCDesktopCapturer> capturer) = 0;
};

/**
 * @brief Screen capture that implements RTCVideoCapturer. Delivers frames to a
 * RTCVideoCapturerDelegate (usually RTCVideoSource).
 */
class RTCDesktopCapturer : public RTCVideoCapturer
{
    Q_OBJECT

  public:
    explicit RTCDesktopCapturer(QSharedPointer<RTCDesktopSource> desktopSource,
                                QSharedPointer<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
                                QSharedPointer<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);
    explicit RTCDesktopCapturer(QSharedPointer<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
                                QSharedPointer<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);

    QSharedPointer<RTCDesktopSource> source() const;

    void startCapture();
    void startCaptureWithFPS(int fps);
    void stopCapture();
    void stopCaptureWithCompletionHandler(std::function<void()> completionHandler);
};

#endif // RTCDESKTOPCAPTURER_H
