#ifndef RTCYUVPLANARBUFFER_H
#define RTCYUVPLANARBUFFER_H

#include <QObject>
#include <QByteArray>

#include "rtcvideoframebuffer.h"

/**
 * @brief Provides methods for handling YUV planar data.
 */
class IRTCYUVPlanarBuffer : public IRTCVideoFrameBuffer
{
  public:
    virtual int chromaWidth() const = 0;
    virtual int chromaHeight() const = 0;
    virtual QByteArray dataY() const = 0;
    virtual QByteArray dataU() const = 0;
    virtual QByteArray dataV() const = 0;
    virtual int strideY() const = 0;
    virtual int strideU() const = 0;
    virtual int strideV() const = 0;
};

#endif // RTCYUVPLANARBUFFER_H
