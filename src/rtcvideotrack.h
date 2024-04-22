#ifndef RTCVIDEOTRACK_H
#define RTCVIDEOTRACK_H

#include <QObject>

#include "rtcmediastreamtrack.h"
#include "rtcvideorenderer.h"
#include "rtcvideosource.h"

class RTCVideoTrackPrivate;

/**
 * @brief Represents a video track with a source and methods to add and remove renderers.
 */
class RTCVideoTrack : public RTCMediaStreamTrack
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCVideoTrack class.
     */
    explicit RTCVideoTrack(RTCVideoTrackPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Returns the video source for this video track.
     * @return The video source.
     */
    RTCVideoSource source() const;

    /**
     * @brief Gets and sets the receive state, if this is a remote video track.
     * @return The receive state.
     */
    bool shouldReceive() const;
    void setShouldReceive(bool shouldReceive);

    /**
     * @brief Registers a renderer that will render all frames received on this track.
     * @param renderer The renderer.
     */
    void addRenderer(IRTCVideoRenderer *renderer);

    /**
     * @brief Deregisters a renderer.
     * @param renderer The renderer.
     */
    void removeRenderer(IRTCVideoRenderer *renderer);
};

#endif // RTCVIDEOTRACK_H
