#include "rtcdatabuffer.h"

RTCDataBuffer::RTCDataBuffer(QObject *parent) : QObject{parent}
{
}

RTCDataBuffer::RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent)
    : QObject{parent}, data_{data}, isBinary_{isBinary}
{
}

QByteArray RTCDataBuffer::data() const
{
    return data_;
}

bool RTCDataBuffer::isBinary() const
{
    return isBinary_;
}
