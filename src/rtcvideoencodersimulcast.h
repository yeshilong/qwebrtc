#ifndef RTCVIDEOENCODERSIMULCAST_H
#define RTCVIDEOENCODERSIMULCAST_H

#include <QObject>

#include "rtcvideoencoderfactory.h"

/**
 * @brief The RTCVideoEncoderSimulcast class.
 */
class RTCVideoEncoderSimulcast : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Gets a simulcast encoder with the specified primary and fallback encoder factories and codec info.
     * @param primary The primary encoder factory.
     * @param fallback The fallback encoder factory.
     * @param videoCodecInfo The codec info.
     * @return The simulcast encoder.
     */
    static IRTCVideoEncoder *simulcastEncoderWithPrimary(IRTCVideoEncoderFactory *primary,
                                                         IRTCVideoEncoderFactory *fallback,
                                                         RTCVideoCodecInfo *videoCodecInfo);
};

#endif // RTCVIDEOENCODERSIMULCAST_H
