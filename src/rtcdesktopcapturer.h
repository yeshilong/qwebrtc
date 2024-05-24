// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RTCDESKTOPCAPTURER_H
#define RTCDESKTOPCAPTURER_H

#include <QObject>
#include <QVector>

#include "rtcdesktopsource.h"
#include "rtcvideocapturer.h"

class CDesktopCapturerDelegate
{
  public:
    virtual void didCaptureFrame(const std::shared_ptr<RTCVideoFrame> frame) = 0;
    virtual void didSourceCaptureStart() = 0;
    virtual void didSourceCapturePause() = 0;
    virtual void didSourceCaptureStop() = 0;
    virtual void didSourceCaptureError() = 0;
};

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

class RTCDesktopCapturerPrivate;
/**
 * @brief Screen capture that implements RTCVideoCapturer. Delivers frames to a
 * RTCVideoCapturerDelegate (usually RTCVideoSource).
 */
class RTCDesktopCapturer : public QObject, public RTCVideoCapturer, public CDesktopCapturerDelegate
{
    Q_OBJECT

  public:
    explicit RTCDesktopCapturer(std::shared_ptr<RTCDesktopSource> desktopSource,
                                std::shared_ptr<IRTCDesktopCapturerDelegate> delegate,
                                std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);
    explicit RTCDesktopCapturer(std::shared_ptr<IRTCDesktopCapturerDelegate> delegate,
                                std::shared_ptr<IRTCVideoCapturerDelegate> captureDelegate,
                                QObject *parent = nullptr);

    ~RTCDesktopCapturer();

    std::shared_ptr<RTCDesktopSource> source() const;

    void startCapture();
    void startCaptureWithFPS(int fps);
    void stopCapture();
    void stopCaptureWithCompletionHandler(std::function<void()> completionHandler);

    void didCaptureFrame(const std::shared_ptr<RTCVideoFrame> frame);
    void didSourceCaptureStart();
    void didSourceCapturePause();
    void didSourceCaptureStop();
    void didSourceCaptureError();

  private:
    RTCDesktopCapturerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDesktopCapturer)
    std::shared_ptr<RTCDesktopSource> desktopSource_;
    std::shared_ptr<IRTCDesktopCapturerDelegate> delegate_;
};

#endif // RTCDESKTOPCAPTURER_H
