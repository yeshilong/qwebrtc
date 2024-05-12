#ifndef RTCVIDEOFRAMEBUFFER_H
#define RTCVIDEOFRAMEBUFFER_H

#include <QObject>
#include <QByteArray>

class RTCI420Buffer;

/**
 * @brief Provides methods for handling video frame buffers.
 */
class IRTCVideoFrameBuffer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoFrameBuffer object.
     */
    explicit IRTCVideoFrameBuffer(QObject *parent = nullptr) : QObject(parent)
    {
    }
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual RTCI420Buffer *toI420() = 0;
    virtual IRTCVideoFrameBuffer *cropAndScaleWith(int offsetX, int offsetY, int cropWidth,
                                                   int cropHeight, int scaleWidth,
                                                   int scaleHeight) = 0;
};

#endif // RTCVIDEOFRAMEBUFFER_H
