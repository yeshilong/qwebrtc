#ifndef RTCVIDEOCAPTURER_H
#define RTCVIDEOCAPTURER_H

#include <QObject>
#include <QSharedPointer>

class RTCVideoFrame;
class RTCVideoCapturer;

/**
 * @brief The IRTCVideoCapturerDelegate class.
 */
class IRTCVideoCapturerDelegate
{
  public:
    virtual void capturer(QSharedPointer<RTCVideoCapturer> capturer,
                          QSharedPointer<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The RTCVideoCapturer class.
 */
class RTCVideoCapturer : public QObject
{
    Q_OBJECT

  public:
    explicit RTCVideoCapturer(QSharedPointer<IRTCVideoCapturerDelegate> videoCapturerDelegate,
                              QObject *parent = nullptr);

    QSharedPointer<IRTCVideoCapturerDelegate> delegate() const;
    void setDelegate(const QSharedPointer<IRTCVideoCapturerDelegate> &delegate);
};

#endif // RTCVIDEOCAPTURER_H
