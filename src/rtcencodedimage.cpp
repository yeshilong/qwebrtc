#include "rtcencodedimage.h"

RTCEncodedImage::RTCEncodedImage(QObject *parent) : QObject{parent}
{
    buffer_ = QByteArray();
    encodedWidth_ = 0;
    encodedHeight_ = 0;
    timeStamp_ = 0;
    captureTimeMs_ = 0;
    ntpTimeMs_ = 0;
    flags_ = 0;
    encodeStartMs_ = 0;
    encodeFinishMs_ = 0;
    frameType_ = RTCFrameType::RTCFrameTypeEmptyFrame;
    rotation_ = RTCVideoRotation::RTCVideoRotation_0;
    qp_ = QVariant(0);
    contentType_ = RTCVideoContentType::RTCVideoContentTypeUnspecified;
}

QByteArray RTCEncodedImage::buffer() const
{
    return buffer_;
}

void RTCEncodedImage::setBuffer(const QByteArray &buffer)
{
    buffer_ = buffer;
}

int32_t RTCEncodedImage::encodedWidth() const
{
    return encodedWidth_;
}

void RTCEncodedImage::setEncodedWidth(int32_t encodedWidth)
{
    encodedWidth_ = encodedWidth;
}

int32_t RTCEncodedImage::encodedHeight() const
{
    return encodedHeight_;
}

void RTCEncodedImage::setEncodedHeight(int32_t encodedHeight)
{
    encodedHeight_ = encodedHeight;
}

uint32_t RTCEncodedImage::timeStamp() const
{
    return timeStamp_;
}

void RTCEncodedImage::setTimeStamp(uint32_t timeStamp)
{
    timeStamp_ = timeStamp;
}

int64_t RTCEncodedImage::captureTimeMs() const
{
    return captureTimeMs_;
}

void RTCEncodedImage::setCaptureTimeMs(int64_t captureTimeMs)
{
    captureTimeMs_ = captureTimeMs;
}

int64_t RTCEncodedImage::ntpTimeMs() const
{
    return ntpTimeMs_;
}

void RTCEncodedImage::setNtpTimeMs(int64_t ntpTimeMs)
{
    ntpTimeMs_ = ntpTimeMs;
}

uint8_t RTCEncodedImage::flags() const
{
    return flags_;
}

void RTCEncodedImage::setFlags(uint8_t flags)
{
    flags_ = flags;
}

int64_t RTCEncodedImage::encodeStartMs() const
{
    return encodeStartMs_;
}

void RTCEncodedImage::setEncodeStartMs(int64_t encodeStartMs)
{
    encodeStartMs_ = encodeStartMs;
}

int64_t RTCEncodedImage::encodeFinishMs() const
{
    return encodeFinishMs_;
}

void RTCEncodedImage::setEncodeFinishMs(int64_t encodeFinishMs)
{
    encodeFinishMs_ = encodeFinishMs;
}

RTCFrameType RTCEncodedImage::frameType() const
{
    return frameType_;
}

void RTCEncodedImage::setFrameType(const RTCFrameType &frameType)
{
    frameType_ = frameType;
}

RTCVideoRotation RTCEncodedImage::rotation() const
{
    return rotation_;
}

void RTCEncodedImage::setRotation(const RTCVideoRotation &rotation)
{
    rotation_ = rotation;
}

QVariant RTCEncodedImage::qp() const
{
    return qp_;
}

void RTCEncodedImage::setQp(const QVariant &qp)
{
    qp_ = qp;
}

RTCVideoContentType RTCEncodedImage::contentType() const
{
    return contentType_;
}

void RTCEncodedImage::setContentType(const RTCVideoContentType &contentType)
{
    contentType_ = contentType;
}
