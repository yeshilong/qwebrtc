#ifndef RTCVIDEOENCODERVP8_H
#define RTCVIDEOENCODERVP8_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderVP8 class.
 */
class RTCVideoEncoderVP8 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderVP8 object.
     */
    explicit RTCVideoEncoderVP8(QObject *parent = nullptr);

    /**
     * @brief Gets a VP8 encoder.
     * @return The VP8 encoder.
     */
    static IRTCVideoEncoder *vp8Encoder();
};

#endif // RTCVIDEOENCODERVP8_H
