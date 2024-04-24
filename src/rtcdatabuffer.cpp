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

RTCDataBuffer::RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent)
    : QObject{parent}, d_ptr{new RTCDataBufferPrivate{data, isBinary}}
{
}

QByteArray RTCDataBuffer::data() const
{
    Q_D(const RTCDataBuffer);
    return QByteArray(reinterpret_cast<const char *>(d_ptr->nativeDataBuffer_->data.data()),
                      d_ptr->nativeDataBuffer_->data.size());
}

bool RTCDataBuffer::isBinary() const
{
    return d_ptr->nativeDataBuffer_->binary;
}
