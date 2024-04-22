#ifndef RTCVIDEODECODERAV1_H
#define RTCVIDEODECODERAV1_H

#include <QObject>
#include <QVector>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCVideoDecoderAV1 class.
 */
class RTCVideoDecoderAV1 : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderAV1 object.
     */
    explicit RTCVideoDecoderAV1(QObject *parent = nullptr);

    /**
     * @brief Gets the AV1 decoder.
     * @return The AV1 decoder.
     */
    static IRTCVideoDecoder *av1Decoder();
};

#endif // RTCVIDEODECODERAV1_H
