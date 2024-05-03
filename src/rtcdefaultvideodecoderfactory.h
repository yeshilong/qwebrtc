#ifndef RTCDEFAULTVIDEODECODERFACTORY_H
#define RTCDEFAULTVIDEODECODERFACTORY_H

#include <QObject>

#include "rtcvideodecoderfactory.h"

/**
 * @brief The RTCDefaultVideoDecoderFactory class.
 */
class RTCDefaultVideoDecoderFactory : public IRTCVideoDecoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCDefaultVideoDecoderFactory object.
     */
    explicit RTCDefaultVideoDecoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates a decoder.
     * @param info The codec info.
     * @return The decoder.
     */
    IRTCVideoDecoder *createDecoder(RTCVideoCodecInfo *info);

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    QVector<RTCVideoCodecInfo *> supportedCodecs();
};

#endif // RTCDEFAULTVIDEODECODERFACTORY_H
