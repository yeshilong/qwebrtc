#ifndef RTCMEDIASTREAM_H
#define RTCMEDIASTREAM_H

#include <QObject>
#include <QVector>
#include <QString>

#include "rtcaudiotrack.h"
#include "rtcvideotrack.h"

/**
 * @brief Represents a media stream.
 */
class RTCMediaStream : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCMediaStream class.
     */
    explicit RTCMediaStream(QObject *parent = nullptr);

    /**
     * @brief Gets the audio tracks in this stream.
     * @return The audio tracks.
     */
    QVector<RTCAudioTrack *> audioTracks() const;

    /**
     * @brief Gets the video tracks in this stream.
     * @return The video tracks.
     */
    QVector<RTCVideoTrack *> videoTracks() const;

    /**
     * @brief Gets an identifier for this media stream.
     * @return The stream ID.
     */
    QString streamId() const;

    /**
     * @brief Adds the given audio track to this media stream.
     * @param audioTrack The audio track.
     */
    void addAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Adds the given video track to this media stream.
     * @param videoTrack The video track.
     */
    void addVideoTrack(RTCVideoTrack *videoTrack);

    /**
     * @brief Removes the given audio track from this media stream.
     * @param audioTrack The audio track.
     */
    void removeAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Removes the given video track from this media stream.
     * @param videoTrack The video track.
     */
    void removeVideoTrack(RTCVideoTrack *videoTrack);
};

#endif // RTCMEDIASTREAM_H
