#include "rtcvideoframe.h"

#include "rtcvideoframebuffer.h"

RTCVideoFrame::RTCVideoFrame(std::shared_ptr<IRTCVideoFrameBuffer> frameBuffer,
                             RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    buffer_ = frameBuffer;
    rotation_ = rotation;
    timeStampNs_ = timeStampNs;
}

RTCVideoFrame::RTCVideoFrame(QObject *pixelBuffer, RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    // Deprecated.
}

RTCVideoFrame::RTCVideoFrame(QObject *pixelBuffer, const QSize &scaledSize, const QRect &cropRect,
                             RTCVideoRotation rotation, qint64 timeStampNs)
    : QObject(nullptr)
{
    // Deprecated.
}

int RTCVideoFrame::width() const
{
    return buffer_->width();
}

int RTCVideoFrame::height() const
{
    return buffer_->height();
}

RTCVideoRotation RTCVideoFrame::rotation() const
{
    return rotation_;
}

qint64 RTCVideoFrame::timeStampNs() const
{
    return timeStampNs_;
}

int RTCVideoFrame::timeStamp() const
{
    return timeStamp_;
}

void RTCVideoFrame::setTimeStamp(int timeStamp)
{
    timeStamp_ = timeStamp;
}

std::shared_ptr<IRTCVideoFrameBuffer> RTCVideoFrame::buffer() const
{
    return buffer_;
}
