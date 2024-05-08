#include "rtcnativei420buffer_p.h"

RTCI420BufferPrivate::RTCI420BufferPrivate() : nativeI420Buffer_()
{
}

RTCI420BufferPrivate::RTCI420BufferPrivate(
    rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer)
    : nativeI420Buffer_(nativeI420Buffer)
{
}

rtc::scoped_refptr<webrtc::I420BufferInterface> RTCI420BufferPrivate::nativeI420Buffer() const
{
    return nativeI420Buffer_;
}

RTCI420Buffer::RTCI420Buffer(int width, int height, QObject *parent)
    : IRTCI420Buffer(width, height), d_ptr(new RTCI420BufferPrivate())
{
    d_ptr->nativeI420Buffer_ = webrtc::I420Buffer::Create(width, height);
}

RTCI420Buffer::RTCI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                             QObject *parent)
    : IRTCI420Buffer(width, height, strideY, strideU, strideV), d_ptr(new RTCI420BufferPrivate())
{
    d_ptr->nativeI420Buffer_ = webrtc::I420Buffer::Create(width, height, strideY, strideU, strideV);
}

RTCI420Buffer::RTCI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                             const uint8_t *dataV, QObject *parent)
    : IRTCI420Buffer(width, height, dataY, dataU, dataV), d_ptr(new RTCI420BufferPrivate())
{
    d_ptr->nativeI420Buffer_ = webrtc::I420Buffer::Copy(width, height, dataY, width, dataU,
                                                        (width + 1) / 2, dataV, (width + 1) / 2);
}

RTCI420Buffer::RTCI420Buffer(RTCI420BufferPrivate &d, QObject *parent)
    : IRTCI420Buffer(parent), d_ptr(&d)
{
}

int RTCI420Buffer::width() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->width();
}

int RTCI420Buffer::height() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->height();
}

IRTCI420Buffer *RTCI420Buffer::toI420()
{
    return this;
}

RTCI420Buffer *RTCI420Buffer::cropAndScaleWith(int offsetX, int offsetY, int cropWidth,
                                               int cropHeight, int scaleWidth, int scaleHeight)
{
    Q_D(RTCI420Buffer);
    rtc::scoped_refptr<webrtc::VideoFrameBuffer> scaled_buffer =
        d_ptr->nativeI420Buffer_->CropAndScale(offsetX, offsetY, cropWidth, cropHeight, scaleWidth,
                                               scaleHeight);
    RTC_DCHECK_EQ(scaled_buffer->type(), webrtc::VideoFrameBuffer::Type::kI420);
    // Calling ToI420() doesn't do any conversions.
    rtc::scoped_refptr<webrtc::I420BufferInterface> buffer = scaled_buffer->ToI420();
    auto i420Private = new RTCI420BufferPrivate(buffer);
    return new RTCI420Buffer(*i420Private);
}

int RTCI420Buffer::chromaWidth() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->ChromaWidth();
}

int RTCI420Buffer::chromaHeight() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->ChromaHeight();
}

const uint8_t *RTCI420Buffer::dataY() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->DataY();
}

const uint8_t *RTCI420Buffer::dataU() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->DataU();
}

const uint8_t *RTCI420Buffer::dataV() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->DataV();
}

int RTCI420Buffer::strideY() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->StrideY();
}

int RTCI420Buffer::strideU() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->StrideU();
}

int RTCI420Buffer::strideV() const
{
    Q_D(const RTCI420Buffer);
    return d->nativeI420Buffer_->StrideV();
}
