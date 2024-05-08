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
    IRTCYUVPlanarBuffer(QObject *parent = nullptr) : IRTCVideoFrameBuffer(parent)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, QObject *parent = nullptr)
        : IRTCVideoFrameBuffer(parent)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, int strideY, int strideU, int strideV,
                        QObject *parent = nullptr)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                        const uint8_t *dataV, QObject *parent = nullptr)
    {
    }

    virtual int chromaWidth() const = 0;
    virtual int chromaHeight() const = 0;
    virtual const uint8_t *dataY() const = 0;
    virtual const uint8_t *dataU() const = 0;
    virtual const uint8_t *dataV() const = 0;
    virtual int strideY() const = 0;
    virtual int strideU() const = 0;
    virtual int strideV() const = 0;
};

#endif // RTCYUVPLANARBUFFER_H
