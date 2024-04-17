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
};

#endif // RTCDEFAULTVIDEODECODERFACTORY_H
