#ifndef RTCVIDEORENDERER_H
#define RTCVIDEORENDERER_H

#include <QObject>
#include <QSize>

class RTCVideoFrame;

/**
 * @brief The IRTCVideoRenderer interface.
 */
class IRTCVideoRenderer
{
  public:
    virtual void setSize(const QSize &size) = 0;
    virtual void renderFrame(QSharedPointer<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The IRTCVideoViewDelegate interface.
 */
class IRTCVideoViewDelegate
{
  public:
    virtual void videoView(QSharedPointer<IRTCVideoRenderer> videoView, const QSize &size) = 0;
};

#endif // RTCVIDEORENDERER_H
