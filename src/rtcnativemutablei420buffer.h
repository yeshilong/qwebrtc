#ifndef RTCNATIVEMUTABLEI420BUFFER_H
#define RTCNATIVEMUTABLEI420BUFFER_H

#include "rtcnativei420buffer.h"
#include "rtcmutableyuvplanarbuffer.h"

class RTCMutableI420BufferPrivate;
class RTCMutableI420Buffer : public RTCI420Buffer, IRTCMutableYUVPlanarBuffer
{
  public:
    const uint8_t *mutableDataY() const override;
    const uint8_t *mutableDataU() const override;
    const uint8_t *mutableDataV() const override;

  protected:
    RTCMutableI420BufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMutableI420Buffer)
};

#endif // RTCNATIVEMUTABLEI420BUFFER_H
