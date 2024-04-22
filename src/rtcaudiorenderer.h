#ifndef RTCAUDIORENDERER_H
#define RTCAUDIORENDERER_H

#include <QObject>
#include <QAudioBuffer>

/**
 * @brief Represents a renderer for audio sample buffers.
 */
class IRTCAudioRenderer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Renders the given audio sample buffer.
     * @param sampleBuffer The audio sample buffer.
     */
    virtual void render(QAudioBuffer sampleBuffer) = 0;
};

#endif // RTCAUDIORENDERER_H
