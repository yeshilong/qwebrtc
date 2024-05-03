#ifndef RTCDEFAULTVIDEOENCODERFACTORY_H
#define RTCDEFAULTVIDEOENCODERFACTORY_H

#include <QObject>

#include "rtcvideoencoderfactory.h"

/**
 * @brief The RTCDefaultVideoEncoderFactory class.
 */
class RTCDefaultVideoEncoderFactory : public IRTCVideoEncoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCDefaultVideoEncoderFactory object.
     */
    explicit RTCDefaultVideoEncoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates an encoder.
     * @param info The codec info.
     * @return The created encoder.
     */
    IRTCVideoEncoder *createEncoder(RTCVideoCodecInfo *info);

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    QVector<RTCVideoCodecInfo *> supportedCodecs();

    /**
     * @brief Gets the implementations.
     * @return The implementations.
     */
    QVector<RTCVideoCodecInfo *> implementations() = 0;

    /**
     * @brief Gets the encoder selector.
     * @return The encoder selector.
     */
    IRTCVideoEncoderSelector *encoderSelector() = 0;

    /**
     * @brief Gets the preferred codec.
     * @return The preferred codec.
     */
    RTCVideoCodecInfo *preferredCodec() const;

    /**
     * @brief Sets the preferred codec.
     * @param codec The preferred codec.
     */
    void setPreferredCodec(RTCVideoCodecInfo *codec);

  private:
    RTCVideoCodecInfo *preferredCodec_;
};

#endif // RTCDEFAULTVIDEOENCODERFACTORY_H
