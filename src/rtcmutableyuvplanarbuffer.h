#ifndef RTCMUTABLEYUVPLANARBUFFER_H
#define RTCMUTABLEYUVPLANARBUFFER_H

#include "rtcyuvplanarbuffer.h"

class IRTCMutableYUVPlanarBuffer : public IRTCYUVPlanarBuffer
{
  public:
    IRTCMutableYUVPlanarBuffer(QObject *parent = nullptr) : IRTCYUVPlanarBuffer(parent)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height) : IRTCYUVPlanarBuffer(width, height)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height, int strideY, int strideU, int strideV)
        : IRTCYUVPlanarBuffer(width, height, strideY, strideU, strideV)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height, uint8_t *dataY, uint8_t *dataU,
                               uint8_t *dataV)
        : IRTCYUVPlanarBuffer(width, height, dataY, dataU, dataV)
    {
    }

    virtual const uint8_t *mutableDataY() const = 0;
    virtual const uint8_t *mutableDataU() const = 0;
    virtual const uint8_t *mutableDataV() const = 0;
};

#endif // RTCMUTABLEYUVPLANARBUFFER_H
