#ifndef RTCVIDEOENCODERFACTORYSIMULCAST_H
#define RTCVIDEOENCODERFACTORYSIMULCAST_H

#include <QObject>

#include "rtcvideoencoderfactory.h"

/**
 * @brief The RTCVideoEncoderFactorySimulcast class.
 */
class RTCVideoEncoderFactorySimulcast : public IRTCVideoEncoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderFactorySimulcast object.
     * @param primary The primary encoder factory.
     * @param fallback The fallback encoder factory.
     */
    explicit RTCVideoEncoderFactorySimulcast(IRTCVideoEncoderFactory *primary,
                                             IRTCVideoEncoderFactory *fallback,
                                             QObject *parent = nullptr);

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

  private:
    IRTCVideoEncoderFactory *primary_;
    IRTCVideoEncoderFactory *fallback_;
};

#endif // RTCVIDEOENCODERFACTORYSIMULCAST_H
