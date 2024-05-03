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

    /**
     * @brief This returns a H264 encoder that can be returned from a RTCVideoEncoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoEncoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the H264 encoder.
     */
    static IRTCVideoEncoder *h264Encoder();

    /**
     * @brief Checks if the H264 encoder is supported.
     * @return True if the H264 encoder is supported, false otherwise.
     */
    static bool isSupported();

    /**
     * @brief Gets the scalability modes.
     * @return The scalability modes.
     */
    static QVector<QString> scalabilityModes();
};

#endif // RTCVIDEOENCODERH264_H
