#ifndef RTCVIDEOENCODERFACTORYH264_H
#define RTCVIDEOENCODERFACTORYH264_H

#include <QObject>

#include "rtcvideoencoderfactory.h"

/**
 * @brief The RTCVideoEncoderFactoryH264 class.
 */
class RTCVideoEncoderFactoryH264 : public IRTCVideoEncoderFactory
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderFactoryH264 object.
     */
    explicit RTCVideoEncoderFactoryH264(QObject *parent = nullptr);
};

#endif // RTCVIDEOENCODERFACTORYH264_H
