// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    return QByteArray(reinterpret_cast<const char *>(d->nativeDataBuffer_->data.data()),
                      d->nativeDataBuffer_->data.size());
}

bool RTCDataBuffer::isBinary() const
{
    Q_D(const RTCDataBuffer);
    return d->nativeDataBuffer_->binary;
}
