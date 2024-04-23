#include "rtcdatabuffer.h"
#include "rtcdatabuffer_p.h"

RTCDataBufferPrivate::RTCDataBufferPrivate(const QByteArray &data, bool isBinary)
{
    rtc::CopyOnWriteBuffer buffer(reinterpret_cast<const uint8_t *>(data.data()), data.size());
    nativeDataBuffer_.reset(new webrtc::DataBuffer(buffer, isBinary));
}

RTCDataBufferPrivate::RTCDataBufferPrivate(const webrtc::DataBuffer &nativeDataBuffer)
{
    nativeDataBuffer_.reset(new webrtc::DataBuffer(nativeDataBuffer));
}

const webrtc::DataBuffer *RTCDataBufferPrivate::nativeDataBuffer() const
{
    return nativeDataBuffer_.get();
}

QByteArray RTCDataBufferPrivate::data() const
{
    return QByteArray(reinterpret_cast<const char *>(nativeDataBuffer_->data.data()),
                      nativeDataBuffer_->data.size());
}

bool RTCDataBufferPrivate::isBinary() const
{
    return nativeDataBuffer_->binary;
}

RTCDataBuffer::RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent)
    : QObject{parent}, d_ptr{new RTCDataBufferPrivate{data, isBinary}}
{
}

QByteArray RTCDataBuffer::data() const
{
    return d_ptr->data();
}

bool RTCDataBuffer::isBinary() const
{
    return d_ptr->isBinary();
}
