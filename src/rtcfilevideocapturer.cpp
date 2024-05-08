#include "rtcfilevideocapturer.h"
#include "rtcvideoframe.h"

#include <QTimer>

#if QT_VERSION >= 0x060000

CVideoSink::CVideoSink(QObject *parent) : QVideoSink(parent)
{
    videoCapturer_ = (RTCFileVideoCapturer *)parent;

    connect(this, &CVideoSink::videoFrameChanged, this, &CVideoSink::present);
}
#else
CVideoSink::CVideoSink(QObject *parent) : QAbstractVideoSurface(parent)
{
    videoCapturer_ = (RTCFileVideoCapturer *)parent;
}
#endif // QT_VERSION >= 0x060000

#if QT_VERSION >= 0x060000
void CVideoSink::present(const QVideoFrame &_frame)
{
    QVideoFrame frame(_frame);
    if (!frame.map(QVideoFrame::ReadOnly))
        return;
    if (!frame.isReadable())
    {
        frame.unmap();
        return;
    }

    switch (frame.pixelFormat())
    {
    case QVideoFrameFormat::Format_XRGB8888:
    case QVideoFrameFormat::Format_YUYV:
    case QVideoFrameFormat::Format_UYVY:
    case QVideoFrameFormat::Format_NV12:
        Q_EMIT frameCaptured(frame);
        break;
    default:
        break;
    }

    frame.unmap();
}
#else
bool CVideoSink::present(const QVideoFrame &_frame)
{
    QVideoFrame frame(_frame);
    if (!frame.map(QAbstractVideoBuffer::ReadOnly))
        return false;
    if (!frame.isReadable())
    {
        frame.unmap();
        return false;
    }

    switch (frame.pixelFormat())
    {
    case QVideoFrame::Format_RGB32:
    case QVideoFrame::Format_YUYV:
    case QVideoFrame::Format_UYVY:
    case QVideoFrame::Format_NV12:
        Q_EMIT frameCaptured(frame);
        break;
    }

    frame.unmap();

    return true;
}

QList<QVideoFrame::PixelFormat> CVideoSink::supportedPixelFormats(
    QAbstractVideoBuffer::HandleType type) const
{
    QList<QVideoFrame::PixelFormat> ret;

    ret.append(QVideoFrame::Format_ARGB32);
    ret.append(QVideoFrame::Format_ARGB32_Premultiplied);
    ret.append(QVideoFrame::Format_RGB32);
    ret.append(QVideoFrame::Format_RGB24);
    ret.append(QVideoFrame::Format_RGB565);
    ret.append(QVideoFrame::Format_RGB555);
    ret.append(QVideoFrame::Format_ARGB8565_Premultiplied);
    ret.append(QVideoFrame::Format_BGRA32);
    ret.append(QVideoFrame::Format_BGRA32_Premultiplied);
    ret.append(QVideoFrame::Format_BGR32);
    ret.append(QVideoFrame::Format_BGR24);
    ret.append(QVideoFrame::Format_BGR565);
    ret.append(QVideoFrame::Format_BGR555);
    ret.append(QVideoFrame::Format_BGRA5658_Premultiplied);
    ret.append(QVideoFrame::Format_AYUV444);
    ret.append(QVideoFrame::Format_AYUV444_Premultiplied);
    ret.append(QVideoFrame::Format_YUV444);
    ret.append(QVideoFrame::Format_YUV420P);
    ret.append(QVideoFrame::Format_YV12);
    ret.append(QVideoFrame::Format_UYVY);
    ret.append(QVideoFrame::Format_YUYV);
    ret.append(QVideoFrame::Format_NV12);
    ret.append(QVideoFrame::Format_NV21);
    ret.append(QVideoFrame::Format_IMC1);
    ret.append(QVideoFrame::Format_IMC2);
    ret.append(QVideoFrame::Format_IMC3);
    ret.append(QVideoFrame::Format_IMC4);
    ret.append(QVideoFrame::Format_Y8);
    ret.append(QVideoFrame::Format_Y16);
    ret.append(QVideoFrame::Format_Jpeg);
    ret.append(QVideoFrame::Format_CameraRaw);
    ret.append(QVideoFrame::Format_AdobeDng);
    ret.append(QVideoFrame::Format_ABGR32);
    ret.append(QVideoFrame::Format_YUV422P);

    return ret;
}
#endif // QT_VERSION >= 0x060000

RTCFileVideoCapturer::RTCFileVideoCapturer(
    std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate, QObject *parent)
    : QObject(parent), IRTCVideoCapturer{videoCapturerDelegate}
{
    mediaPlayer_ = new QMediaPlayer;
    videoSink_ = new CVideoSink(this);
    QObject::connect(videoSink_, &CVideoSink::frameCaptured, this,
                     &RTCFileVideoCapturer::publishSampleBuffer);
}

RTCFileVideoCapturer::~RTCFileVideoCapturer()
{
    stopCapture();
}

void RTCFileVideoCapturer::startCapturingFromFileNamed(const QString &nameOfFile)
{
    lastPresentationTime_ = 0;
    fileUrl_ = QUrl::fromLocalFile(nameOfFile);

#if QT_VERSION >= 0x060000
    mediaPlayer_->setSource(fileUrl_);
#else
    mediaPlayer_->setMedia(fileUrl_);
#endif // QT_VERSION >= 0x060000

    if (mediaPlayer_->error() != QMediaPlayer::NoError)
    {
        Q_EMIT errorOccurred(mediaPlayer_->errorString());
        return;
    }

    mediaPlayer_->setVideoOutput(this);
    mediaPlayer_->play();

    qDebug() << "File capturer started reading";
}

void RTCFileVideoCapturer::stopCapture()
{
    mediaPlayer_->stop();
    qDebug() << "File capturer stopped.";
}

QTimer *RTCFileVideoCapturer::createStrictTimer()
{
    QTimer *timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    return timer;
}

void RTCFileVideoCapturer::publishSampleBuffer(const QVideoFrame &frame)
{
    qint64 presentationTimeNs = frame.startTime();
    qint64 presentationDifferenceNs = presentationTimeNs - lastPresentationTime_;
    lastPresentationTime_ = presentationTimeNs;

    // Create a single-shot timer for the presentation difference
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(presentationDifferenceNs);
    connect(timer, &QTimer::timeout, this, [this, frame]() { Q_EMIT frameCaptured(frame); });
    timer->start();
}
