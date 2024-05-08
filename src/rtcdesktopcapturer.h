#ifndef RTCDESKTOPCAPTURER_H
#define RTCDESKTOPCAPTURER_H

#include <QObject>
#include <QVector>

#include "rtcdesktopsource.h"
#include "rtcvideocapturer.h"

class RTCDesktopCapturer;

/**
 * @brief The IRTCDesktopCapturerDelegate class.
 */
class IRTCDesktopCapturerDelegate
{
  public:
    virtual void didSourceCaptureStart(std::shared_ptr<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCapturePaused(std::shared_ptr<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCaptureStop(std::shared_ptr<RTCDesktopCapturer> capturer) = 0;
    virtual void didSourceCaptureError(std::shared_ptr<RTCDesktopCapturer> capturer) = 0;
};

/**
 * @brief Screen capture that implements IRTCVideoCapturer. Delivers frames to a
 * RTCVideoCapturerDelegate (usually RTCVideoSource).
 */
class RTCDesktopCapturer : public QObject, IRTCVideoCapturer
{
    Q_OBJECT

  public:
    explicit RTCDesktopCapturer(std::shared_ptr<RTCDesktopSource> desktopSource,
                                std::shared_ptr<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
                                std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);
    explicit RTCDesktopCapturer(std::shared_ptr<IRTCDesktopCapturerDelegate> desktopCaptureDelegate,
                                std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);

    std::shared_ptr<RTCDesktopSource> source() const;

    void startCapture();
    void startCaptureWithFPS(int fps);
    void stopCapture();
    void stopCaptureWithCompletionHandler(std::function<void()> completionHandler);
};

#endif // RTCDESKTOPCAPTURER_H
