#ifndef RTCVIDEODECODERAV1_H
#define RTCVIDEODECODERAV1_H

#include <QObject>
#include <QVector>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderAV1 class represents an AV1 video decoder.
 *
 * This class implements the RTCVideoDecoder interface and can be used with a
 * RTCVideoDecoderFactory injected into RTCPeerConnectionFactory.
 */
class RTCVideoDecoderAV1 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Creates an instance of the AV1 video decoder.
     * @return A pointer to the AV1 video decoder.
     *
     * This method returns an AV1 decoder that can be used with a
     * RTCVideoDecoderFactory injected into RTCPeerConnectionFactory.
     */
    explicit RTCVideoDecoderAV1(QObject *parent = nullptr);

    /**
     * @brief Gets the AV1 decoder.
     * @return The AV1 decoder.
     */
    static IRTCVideoDecoder *av1Decoder();
};

#endif // RTCVIDEODECODERAV1_H
