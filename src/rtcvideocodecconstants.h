#ifndef RTCVIDEOCODECCONSTANTS_H
#define RTCVIDEOCODECCONSTANTS_H

#include <QObject>
#include <QString>

/**
 * @brief The RTCVideoCodecConstants class.
 */
class RTCVideoCodecConstants : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoCodecConstants object.
     */
    RTCVideoCodecConstants(QObject *parent = nullptr) = delete;

    /**
     * @brief Gets the VP8 video codec name.
     * @return The VP8 video codec name.
     */
    static QString RTCVideoCodecVp8Name();

    /**
     * @brief Gets the VP9 video codec name.
     * @return The VP9 video codec name.
     */
    static QString RTCVideoCodecVp9Name();

    /**
     * @brief Gets the AV1 video codec name.
     * @return The AV1 video codec name.
     */
    static QString RTCVideoCodecAv1Name();

    /**
     * @brief Gets the H264 video codec name.
     * @return The H264 video codec name.
     */
    static QString RTCVideoCodecH264Name();
};

#endif // RTCVIDEOCODECCONSTANTS_H
