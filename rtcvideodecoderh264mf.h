#ifndef RTCVIDEODECODERH264MF_H
#define RTCVIDEODECODERH264MF_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderH264MF class.
 */
class RTCVideoDecoderH264MF : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderH264MF object.
     */
    explicit RTCVideoDecoderH264MF(QObject *parent = nullptr);

    /**
     * @brief Gets the H264 MF decoder.
     * @return The H264 MF decoder.
     */
    static IRTCVideoDecoder *h264MfDecoder();

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    static QVector<RTCVideoCodecInfo *> supportedCodecs();
};

#endif // RTCVIDEODECODERH264MF_H
