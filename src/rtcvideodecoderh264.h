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

    /**
     * @brief This returns a H264 decoder that can be returned from a RTCVideoDecoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoDecoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     * @return A pointer to the H264 decoder.
     */
    static IRTCVideoDecoder *h264Decoder();

    /**
     * @brief Checks if the H264 decoder is supported.
     * @return True if the H264 decoder is supported, false otherwise.
     */
    static bool isSupported();
};

#endif // RTCVIDEODECODERH264_H
