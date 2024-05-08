#ifndef RTCVIDEOCAPTURER_H
#define RTCVIDEOCAPTURER_H

#include <QObject>

class RTCVideoFrame;
class IRTCVideoCapturer;

/**
 * @brief The IRTCVideoCapturerDelegate class.
 */
class IRTCVideoCapturerDelegate
{
  public:
    virtual void capturer(std::shared_ptr<IRTCVideoCapturer> capturer,
                          std::shared_ptr<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The IRTCVideoCapturer class.
 */
class IRTCVideoCapturer
{
  public:
    explicit IRTCVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate);

    std::shared_ptr<IRTCVideoCapturerDelegate> delegate() const;
    void setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate);
};

#endif // RTCVIDEOCAPTURER_H
