#ifndef RTCVIDEODECODERVP8_H
#define RTCVIDEODECODERVP8_H

#include <QObject>

#include "rtcvideodecoder.h"

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
     * @return This returns a VP8 decoder that can be returned from a RTCVideoDecoderFactory injected into
     * RTCPeerConnectionFactory. Even though it implements the RTCVideoDecoder protocol, it can not be
     * used independently from the RTCPeerConnectionFactory.
     */
    static IRTCVideoDecoder *vp8Decoder();
};

#endif // RTCVIDEODECODERVP8_H
