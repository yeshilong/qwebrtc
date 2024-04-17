#ifndef RTCVIDEODECODERFACTORYH264_H
#define RTCVIDEODECODERFACTORYH264_H

#include <QObject>

#include "rtcvideodecoderfactory.h"

/**
 * @brief The RTCVideoDecoderFactoryH264 class.
 */
class RTCVideoDecoderFactoryH264 : public IRTCVideoDecoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoDecoderFactoryH264 object.
     */
    explicit RTCVideoDecoderFactoryH264(QObject *parent = nullptr);
};

#endif // RTCVIDEODECODERFACTORYH264_H
