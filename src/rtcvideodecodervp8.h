#ifndef RTCVIDEODECODERVP8_H
#define RTCVIDEODECODERVP8_H

#include <QObject>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderVP8 class.
 */
class RTCVideoDecoderVP8 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderVP8 object.
     */
    explicit RTCVideoDecoderVP8(QObject *parent = nullptr);

    /**
     * @brief Gets the VP8 decoder.
     * @return The VP8 decoder.
     */
    static IRTCVideoDecoder *vp8Decoder();
};

#endif // RTCVIDEODECODERVP8_H
