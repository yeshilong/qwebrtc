#ifndef RTCMEDIASTREAMTRACK_H
#define RTCMEDIASTREAMTRACK_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

/**
 * @brief Represents a media stream track with multiple properties.
 */
class RTCMediaStreamTrack : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Creates a new instance.
     * @param parent The parent object.
     */
    explicit RTCMediaStreamTrack(QObject *parent = nullptr);

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
};

#endif // RTCMEDIASTREAMTRACK_H
