#ifndef RTCVIDEODECODERVP9_H
#define RTCVIDEODECODERVP9_H

#include <QObject>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderVP9 class.
 */
class RTCVideoDecoderVP9 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderVP9 object.
     */
    explicit RTCVideoDecoderVP9(QObject *parent = nullptr);

    /**
     * @brief Gets the VP9 decoder.
     * @return The VP9 decoder.
     */
    static IRTCVideoDecoder *vp9Decoder();

    /**
     * @brief Checks if the VP9 decoder is supported.
     * @return True if the VP9 decoder is supported, false otherwise.
     */
    static bool isSupported();
};

#endif // RTCVIDEODECODERVP9_H
