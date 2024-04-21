#ifndef RTCVIDEOENCODERVP9_H
#define RTCVIDEOENCODERVP9_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderVP9 class.
 */
class RTCVideoEncoderVP9 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderVP9 object.
     */
    explicit RTCVideoEncoderVP9(QObject *parent = nullptr);

    /**
     * @brief Gets a VP9 encoder.
     * @return The VP9 encoder.
     */
    static IRTCVideoEncoder *vp9Encoder();

    /**
     * @brief Checks if the VP9 encoder is supported.
     * @return True if the VP9 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Gets the scalability modes.
     * @return The scalability modes.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERVP9_H