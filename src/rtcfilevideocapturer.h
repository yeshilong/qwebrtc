#ifndef RTCFILEVIDEOCAPTURER_H
#define RTCFILEVIDEOCAPTURER_H

#include <QObject>
#include <QString>

#include "rtcerror.h"
#include "rtcvideocapturer.h"

/**
 * @brief Delegate for handling errors.
 */
using RTCFileVideoCapturerErrorBlock = std::function<void(RTCError *)>;

/**
 * @brief Captures buffers from bundled video file.
 */
class RTCFileVideoCapturer : public QObject, IRTCVideoCapturer
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCFileVideoCapturer class.
     */
    explicit RTCFileVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate,
                                  QObject *parent = nullptr);

    /**
     * @brief Starts asynchronous capture of frames from video file.
     */
    void startCapturingFromFileNamed(const QString &nameOfFile,
                                     RTCFileVideoCapturerErrorBlock errorBlock);

    /**
     * @brief Immediately stops capture.
     */
    void stopCapture();
};

#endif // RTCFILEVIDEOCAPTURER_H
