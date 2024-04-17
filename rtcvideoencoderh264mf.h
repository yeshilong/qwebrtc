#ifndef RTCVIDEOENCODERH264MF_H
#define RTCVIDEOENCODERH264MF_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderH264MF class.
 */
class RTCVideoEncoderH264MF : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderH264MF object.
     */
    explicit RTCVideoEncoderH264MF(QObject *parent = nullptr);

    /**
     * @brief Gets a H264 MF encoder.
     * @return The H264 MF encoder.
     */
    static IRTCVideoEncoder *h264MFEncoder();

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    static QVector<RTCVideoCodecInfo *> supportedCodecs();
};

#endif // RTCVIDEOENCODERH264MF_H
