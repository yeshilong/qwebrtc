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
};

#endif // RTCVIDEOENCODERFACTORYSIMULCAST_H
