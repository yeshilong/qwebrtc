#ifndef RTCNATIVEI420BUFFER_H
#define RTCNATIVEI420BUFFER_H

#include <QString>

#include "rtci420buffer.h"

class RTCI420BufferPrivate;
/**
 * @brief Implements the IRTCI420Buffer interface.
 */
class RTCI420Buffer : public IRTCI420Buffer
{
  public:
    RTCI420Buffer();

    /**
     * @brief Constructs an IRTCVideoFrameBuffer object.
     */
    RTCI420Buffer(QObject *parent = nullptr) : IRTCI420Buffer(parent)
    {
    }

    explicit RTCI420Buffer(int width, int height, QObject *parent = nullptr);
    RTCI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                  QObject *parent = nullptr);
    RTCI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                  const uint8_t *dataV, QObject *parent = nullptr);

    int width() const;
    int height() const;

    IRTCI420Buffer *toI420();
    RTCI420Buffer *cropAndScaleWith(int offsetX, int offsetY, int cropWidth, int cropHeight,
                                    int scaleWidth, int scaleHeight);

    int chromaWidth() const;
    int chromaHeight() const;
    const uint8_t *dataY() const;
    const uint8_t *dataU() const;
    const uint8_t *dataV() const;
    int strideY() const;
    int strideU() const;
    int strideV() const;

  public:
    RTCI420Buffer(RTCI420BufferPrivate &d, QObject *parent = nullptr);

  private:
    RTCI420BufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCI420Buffer)
};

#endif // RTCNATIVEI420BUFFER_H
