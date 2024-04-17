#ifndef RTCVIDEODECODERH264_H
#define RTCVIDEODECODERH264_H

#include <QObject>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderH264 class.
 */
class RTCVideoDecoderH264 : public IRTCVideoDecoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderH264 object.
     */
    explicit RTCVideoDecoderH264(QObject *parent = nullptr);
};

#endif // RTCVIDEODECODERH264_H
