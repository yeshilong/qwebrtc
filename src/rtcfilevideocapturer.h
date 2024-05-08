#ifndef RTCFILEVIDEOCAPTURER_H
#define RTCFILEVIDEOCAPTURER_H

#include <QMediaPlayer>
#include <QVideoFrame>
#if QT_VERSION >= 0x060000
#include <QCameraDevice>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QVideoSink>
#else
#include <QAbstractVideoSurface>
#include <QCameraInfo>
#include <QVideoSurfaceFormat>
#endif // QT_VERSION >= 0x060000

#include "rtcvideocapturer.h"

class RTCFileVideoCapturer;

#if QT_VERSION >= 0x060000
class CVideoSink : public QVideoSink
{
#else
class CVideoSink : public QAbstractVideoSurface
{
#endif // QT_VERSION >= 0x060000

    Q_OBJECT

  public:
    CVideoSink(QObject *parent = nullptr);

#if QT_VERSION >= 0x060000
  public Q_SLOTS:
    void present(const QVideoFrame &frame);
#else
    bool present(const QVideoFrame &frame) override;
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
        QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const override;
#endif // QT_VERSION >= 0x060000

  Q_SIGNALS:
    void frameCaptured(const QVideoFrame &frame);

  private:
    RTCFileVideoCapturer *videoCapturer_;
};

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
     * @brief Destroys the RTCFileVideoCapturer object.
     */
    ~RTCFileVideoCapturer();

    /**
     * @brief Starts asynchronous capture of frames from a video file.
     * 
     * This function starts the asynchronous capture of frames from a video file. If an error occurs, 
     * the capturing process will not start. Any underlying error will be relayed to the provided 
     * error handling function (if one is provided). Successfully captured video frames will be 
     * passed to the delegate.
     * 
     * @param nameOfFile A QString representing the name of the video file to be read. This should be 
     * a bundled video file.
     * @param errorBlock A function to be executed upon encountering an error. This function should 
     * take a single parameter of type std::exception (or a derived type) and return void.
     */
    void startCapturingFromFileNamed(const QString &nameOfFile);

    /**
     * @brief Immediately stops capture.
     */
    void stopCapture();

  Q_SIGNALS:
    void errorOccurred(const QString &description);
    void frameCaptured(const QVideoFrame &frame);

  private:
    QTimer *createStrictTimer();
    void publishSampleBuffer(const QVideoFrame &sampleBuffer);

    QMediaPlayer *mediaPlayer_;
    qint64 lastPresentationTime_;
    QUrl fileUrl_;
    CVideoSink *videoSink_;
    IRTCVideoCapturerDelegate *videoCapturerDelegate_;
};

#endif // RTCFILEVIDEOCAPTURER_H
