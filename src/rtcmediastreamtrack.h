#ifndef RTCMEDIASTREAMTRACK_H
#define RTCMEDIASTREAMTRACK_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCMediaStreamTrackPrivate;

/**
 * @brief Represents a media stream track with multiple properties.
 */
class RTCMediaStreamTrack : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Returns the kind of track. For example, "audio" if this track represents an audio track and "video" if this track represents a video track.
     * @return The kind of track.
     */
    QString kind() const;

    /**
     * @brief Returns the identifier of the track.
     * @return The track identifier.
     */
    QString trackId() const;

    /**
     * @brief Gets and sets the enabled state of the track.
     * @return The enabled state of the track.
     */
    bool isEnabled() const;
    void setIsEnabled(bool isEnabled);

    /**
     * @brief Returns the state of the track.
     * @return The state of the track.
     */
    RTCMediaStreamTrackState readyState() const;

    /**
     * @brief Returns the kind of audio track.
     * @return The kind of audio track.
     */
    static QString RTCMediaStreamTrackKindAudio();

    /**
     * @brief Returns the kind of video track.
     * @return The kind of video track.
     */
    static QString RTCMediaStreamTrackKindVideo();

  protected:
    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCMediaStreamTrack(RTCMediaStreamTrackPrivate &nativeMediaStreamTrack,
                        QObject *parent = nullptr);

    RTCMediaStreamTrackPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaStreamTrack)
};

#endif // RTCMEDIASTREAMTRACK_H
