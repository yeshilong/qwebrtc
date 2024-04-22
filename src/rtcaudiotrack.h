#ifndef RTCAUDIOTRACK_H
#define RTCAUDIOTRACK_H

#include <QObject>

#include "rtcaudiorenderer.h"
#include "rtcaudiosource.h"
#include "rtcmediastreamtrack.h"

class RTCAudioTrackPrivate;
/**
 * @brief Represents an audio track with a source and methods to add and remove renderers.
 */
class RTCAudioTrack : public RTCMediaStreamTrack
{
    Q_OBJECT

  public:
    /**
     * @brief Creates a new instance.
     * @param parent The parent object.
     */
    explicit RTCAudioTrack(RTCAudioTrackPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Returns the audio source for this audio track.
     * @return The audio source.
     */
    RTCAudioSource source() const;

    /**
     * @brief Registers a renderer that will receive all audio sample buffers on this track.
     * @param renderer The renderer.
     */
    void addRenderer(IRTCAudioRenderer *renderer);

    /**
     * @brief Deregisters a renderer.
     * @param renderer The renderer.
     */
    void removeRenderer(IRTCAudioRenderer *renderer);
};

#endif // RTCAUDIOTRACK_H
