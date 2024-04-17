#ifndef RTCVIDEOENCODERH264_H
#define RTCVIDEOENCODERH264_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The RTCVideoEncoderH264 class.
 */
class RTCVideoEncoderH264 : public IRTCVideoEncoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderH264 object.
     * @param codecInfo The codec info.
     */
    explicit RTCVideoEncoderH264(RTCVideoCodecInfo *codecInfo, QObject *parent = nullptr);
};

#endif // RTCVIDEOENCODERH264_H
