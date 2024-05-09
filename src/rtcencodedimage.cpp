#include "rtcencodedimage_p.h"

#include "rtc_base/numerics/safe_conversions.h"

namespace
{
// An implementation of EncodedImageBufferInterface that doesn't perform any copies.
class CEncodedImageBuffer : public webrtc::EncodedImageBufferInterface
{
  public:
    static rtc::scoped_refptr<CEncodedImageBuffer> Create(QByteArray data)
    {
        return rtc::make_ref_counted<CEncodedImageBuffer>(data);
    }
    const uint8_t *data() const override
    {
        return reinterpret_cast<const uint8_t *>(data_.constData());
    }
    // TODO(bugs.webrtc.org/9378): delete this non-const data method.
    uint8_t *data() override
    {
        return const_cast<uint8_t *>(reinterpret_cast<const uint8_t *>(data_.constData()));
    }
    size_t size() const override
    {
        return data_.size();
    }

  protected:
    explicit CEncodedImageBuffer(QByteArray data) : data_(std::move(data))
    {
    }
    ~CEncodedImageBuffer()
    {
    }

    QByteArray data_;
};
} // namespace

RTCEncodedImagePrivate::RTCEncodedImagePrivate()
{
}

RTCEncodedImagePrivate::RTCEncodedImagePrivate(const webrtc::EncodedImage &nativeEncodedImage)
{
    encodedImageBuffer_ = nativeEncodedImage.GetEncodedData();
    encodedWidth_ = rtc::dchecked_cast<int32_t>(nativeEncodedImage._encodedWidth);
    encodedHeight_ = rtc::dchecked_cast<int32_t>(nativeEncodedImage._encodedHeight);
    timeStamp_ = nativeEncodedImage.Timestamp();
    captureTimeMs_ = nativeEncodedImage.capture_time_ms_;
    ntpTimeMs_ = nativeEncodedImage.ntp_time_ms_;
    flags_ = nativeEncodedImage.timing_.flags;
    encodeStartMs_ = nativeEncodedImage.timing_.encode_start_ms;
    encodeFinishMs_ = nativeEncodedImage.timing_.encode_finish_ms;
    frameType_ = static_cast<RTCFrameType>(nativeEncodedImage._frameType);
    rotation_ = static_cast<RTCVideoRotation>(nativeEncodedImage.rotation_);
    qp_ = nativeEncodedImage.qp_;
    contentType_ = (nativeEncodedImage.content_type_ == webrtc::VideoContentType::SCREENSHARE)
                       ? RTCVideoContentType::RTCVideoContentTypeScreenshare
                       : RTCVideoContentType::RTCVideoContentTypeUnspecified;
    buffer_ = QByteArray::fromRawData(reinterpret_cast<const char *>(encodedImageBuffer_->data()),
                                      nativeEncodedImage.size());
}

webrtc::EncodedImage RTCEncodedImagePrivate::nativeEncodedImage() const
{
    webrtc::EncodedImage encodedImage;
    if (encodedImageBuffer_)
    {
        encodedImage.SetEncodedData(encodedImageBuffer_);
    }
    else if (!buffer_.isNull())
    {
        encodedImage.SetEncodedData(CEncodedImageBuffer::Create(buffer_));
    }
    encodedImage.set_size(buffer_.size());
    encodedImage._encodedWidth = rtc::dchecked_cast<uint32_t>(encodedWidth_);
    encodedImage._encodedHeight = rtc::dchecked_cast<uint32_t>(encodedHeight_);
    encodedImage.SetTimestamp(timeStamp_);
    encodedImage.capture_time_ms_ = captureTimeMs_;
    encodedImage.ntp_time_ms_ = ntpTimeMs_;
    encodedImage.timing_.flags = flags_;
    encodedImage.timing_.encode_start_ms = encodeStartMs_;
    encodedImage.timing_.encode_finish_ms = encodeFinishMs_;
    encodedImage._frameType = static_cast<webrtc::VideoFrameType>(frameType_);
    encodedImage.rotation_ = static_cast<webrtc::VideoRotation>(rotation_);
    encodedImage.qp_ = qp_.isNull() ? qp_.toInt() : -1;
    encodedImage.content_type_ =
        (contentType_ == RTCVideoContentType::RTCVideoContentTypeScreenshare)
            ? webrtc::VideoContentType::SCREENSHARE
            : webrtc::VideoContentType::UNSPECIFIED;
    return encodedImage;
}

RTCEncodedImage::RTCEncodedImage(QObject *parent)
    : QObject{parent}, d_ptr{new RTCEncodedImagePrivate{}}
{
}

RTCEncodedImage::RTCEncodedImage(RTCEncodedImagePrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QByteArray RTCEncodedImage::buffer() const
{
    Q_D(const RTCEncodedImage);
    return d->buffer_;
}

void RTCEncodedImage::setBuffer(const QByteArray &buffer)
{
    Q_D(RTCEncodedImage);
    d->buffer_ = buffer;
}

int32_t RTCEncodedImage::encodedWidth() const
{
    Q_D(const RTCEncodedImage);
    return d->encodedWidth_;
}

void RTCEncodedImage::setEncodedWidth(int32_t encodedWidth)
{
    Q_D(RTCEncodedImage);
    d->encodedWidth_ = encodedWidth;
}

int32_t RTCEncodedImage::encodedHeight() const
{
    Q_D(const RTCEncodedImage);
    return d->encodedHeight_;
}

void RTCEncodedImage::setEncodedHeight(int32_t encodedHeight)
{
    Q_D(RTCEncodedImage);
    d->encodedHeight_ = encodedHeight;
}

uint32_t RTCEncodedImage::timeStamp() const
{
    Q_D(const RTCEncodedImage);
    return d->timeStamp_;
}

void RTCEncodedImage::setTimeStamp(uint32_t timeStamp)
{
    Q_D(RTCEncodedImage);
    d->timeStamp_ = timeStamp;
}

int64_t RTCEncodedImage::captureTimeMs() const
{
    Q_D(const RTCEncodedImage);
    return d->captureTimeMs_;
}

void RTCEncodedImage::setCaptureTimeMs(int64_t captureTimeMs)
{
    Q_D(RTCEncodedImage);
    d->captureTimeMs_ = captureTimeMs;
}

int64_t RTCEncodedImage::ntpTimeMs() const
{
    Q_D(const RTCEncodedImage);
    return d->ntpTimeMs_;
}

void RTCEncodedImage::setNtpTimeMs(int64_t ntpTimeMs)
{
    Q_D(RTCEncodedImage);
    d->ntpTimeMs_ = ntpTimeMs;
}

uint8_t RTCEncodedImage::flags() const
{
    Q_D(const RTCEncodedImage);
    return d->flags_;
}

void RTCEncodedImage::setFlags(uint8_t flags)
{
    Q_D(RTCEncodedImage);
    d->flags_ = flags;
}

int64_t RTCEncodedImage::encodeStartMs() const
{
    Q_D(const RTCEncodedImage);
    return d->encodeStartMs_;
}

void RTCEncodedImage::setEncodeStartMs(int64_t encodeStartMs)
{
    Q_D(RTCEncodedImage);
    d->encodeStartMs_ = encodeStartMs;
}

int64_t RTCEncodedImage::encodeFinishMs() const
{
    Q_D(const RTCEncodedImage);
    return d->encodeFinishMs_;
}

void RTCEncodedImage::setEncodeFinishMs(int64_t encodeFinishMs)
{
    Q_D(RTCEncodedImage);
    d->encodeFinishMs_ = encodeFinishMs;
}

RTCFrameType RTCEncodedImage::frameType() const
{
    Q_D(const RTCEncodedImage);
    return d->frameType_;
}

void RTCEncodedImage::setFrameType(const RTCFrameType &frameType)
{
    Q_D(RTCEncodedImage);
    d->frameType_ = frameType;
}

RTCVideoRotation RTCEncodedImage::rotation() const
{
    Q_D(const RTCEncodedImage);
    return d->rotation_;
}

void RTCEncodedImage::setRotation(const RTCVideoRotation &rotation)
{
    Q_D(RTCEncodedImage);
    d->rotation_ = rotation;
}

QVariant RTCEncodedImage::qp() const
{
    Q_D(const RTCEncodedImage);
    return d->qp_;
}

void RTCEncodedImage::setQp(const QVariant &qp)
{
    Q_D(RTCEncodedImage);
    d->qp_ = qp;
}

RTCVideoContentType RTCEncodedImage::contentType() const
{
    Q_D(const RTCEncodedImage);
    return d->contentType_;
}

void RTCEncodedImage::setContentType(const RTCVideoContentType &contentType)
{
    Q_D(RTCEncodedImage);
    d->contentType_ = contentType;
}
