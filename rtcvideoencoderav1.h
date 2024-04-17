#ifndef RTCVIDEOENCODERAV1_H
#define RTCVIDEOENCODERAV1_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderAV1 class.
 */
class RTCVideoEncoderAV1 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderAV1 object.
     */
    explicit RTCVideoEncoderAV1(QObject *parent = nullptr);

    /**
     * @brief Gets the AV1 encoder.
     * @return The AV1 encoder.
     */
    static IRTCVideoEncoder *av1Encoder();

    /**
     * @brief Checks if the AV1 encoder is supported.
     * @return True if the AV1 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Gets the scalability modes.
     * @return The scalability modes.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERAV1_H
