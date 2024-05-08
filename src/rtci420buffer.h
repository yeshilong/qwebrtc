#ifndef RTCI420BUFFER_H
#define RTCI420BUFFER_H

#include "rtcyuvplanarbuffer.h"

/**
 * @brief Provides methods for handling I420 data.
 */
class IRTCI420Buffer : public IRTCYUVPlanarBuffer
{
  public:
    IRTCI420Buffer(QObject *parent = nullptr) : IRTCYUVPlanarBuffer(parent)
    {
    }
    IRTCI420Buffer(int width, int height, QObject *parent = nullptr)
        : IRTCYUVPlanarBuffer(width, height)
    {
    }
    IRTCI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                   QObject *parent = nullptr)
        : IRTCYUVPlanarBuffer(width, height, strideY, strideU, strideV)
    {
    }
    IRTCI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                   const uint8_t *dataV, QObject *parent = nullptr)
        : IRTCYUVPlanarBuffer(width, height, dataY, dataU, dataV)
    {
    }
};

#endif // RTCI420BUFFER_H
