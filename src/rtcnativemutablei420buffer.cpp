#include "rtcnativemutablei420buffer.h"
#include "rtcnativemutablei420buffer_p.h"

#include "api/video/i420_buffer.h"

const uint8_t *RTCMutableI420Buffer::mutableDataY() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataY();
}

const uint8_t *RTCMutableI420Buffer::mutableDataU() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataU();
}

const uint8_t *RTCMutableI420Buffer::mutableDataV() const
{
    Q_D(const RTCMutableI420Buffer);
    return static_cast<webrtc::I420Buffer *>(d->nativeI420Buffer_.get())->MutableDataV();
}
