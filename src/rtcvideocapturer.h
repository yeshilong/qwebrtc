#ifndef RTCVIDEOCAPTURER_H
#define RTCVIDEOCAPTURER_H

#include <QObject>

class RTCVideoFrame;
class RTCVideoCapturer;

/**
 * @brief The IRTCVideoCapturerDelegate class.
 */
class IRTCVideoCapturerDelegate
{
  public:
    virtual void capturer(std::shared_ptr<RTCVideoCapturer> capturer,
                          std::shared_ptr<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The RTCVideoCapturer class.
 */
class RTCVideoCapturer
{
  public:
    explicit RTCVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate);

    std::shared_ptr<IRTCVideoCapturerDelegate> delegate() const;
    void setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate);

  private:
    std::shared_ptr<IRTCVideoCapturerDelegate> delegate_;
};

#endif // RTCVIDEOCAPTURER_H
