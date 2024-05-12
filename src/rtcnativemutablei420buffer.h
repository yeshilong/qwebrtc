#ifndef RTCNATIVEMUTABLEI420BUFFER_H
#define RTCNATIVEMUTABLEI420BUFFER_H

#include "rtcnativei420buffer.h"
#include "rtcmutableyuvplanarbuffer.h"

class RTCMutableI420BufferPrivate;
class RTCMutableI420Buffer : public RTCI420Buffer, public IRTCMutableYUVPlanarBuffer
{
  public:
    RTCMutableI420Buffer(int width, int height, QObject *parent = nullptr)
        : RTCI420Buffer(width, height, parent)
    {
    }
    RTCMutableI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                         QObject *parent = nullptr)
        : RTCI420Buffer(width, height, strideY, strideU, strideV, parent)
    {
    }

    RTCMutableI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                         const uint8_t *dataV, QObject *parent = nullptr)
        : RTCI420Buffer(width, height, dataY, dataU, dataV, parent)
    {
    }
    uint8_t *mutableDataY() const override;
    uint8_t *mutableDataU() const override;
    uint8_t *mutableDataV() const override;

  protected:
    RTCMutableI420BufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMutableI420Buffer)
};

#endif // RTCNATIVEMUTABLEI420BUFFER_H
