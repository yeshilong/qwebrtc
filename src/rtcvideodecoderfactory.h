#ifndef RTCVIDEODECODERFACTORY_H
#define RTCVIDEODECODERFACTORY_H

#include <QObject>

#include "rtcvideocodecinfo.h"
#include "rtcvideodecoder.h"

/**
 * @brief The IRTCVideoDecoderFactory interface.
 */
class IRTCVideoDecoderFactory : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoDecoderFactory object.
     */
    explicit IRTCVideoDecoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates a decoder.
     * @param info The codec info.
     * @return The decoder.
     */
    virtual IRTCVideoDecoder *createDecoder(RTCVideoCodecInfo *info) = 0;

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    virtual QVector<RTCVideoCodecInfo *> supportedCodecs() = 0;
};
#endif // RTCVIDEODECODERFACTORY_H
