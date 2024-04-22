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
     * @brief Gets the preferred codec.
     * @return The preferred codec.
     */
    RTCVideoCodecInfo *preferredCodec() const;

    /**
     * @brief Sets the preferred codec.
     * @param codec The preferred codec.
     */
    void setPreferredCodec(RTCVideoCodecInfo *codec);
};

#endif // RTCDEFAULTVIDEOENCODERFACTORY_H
