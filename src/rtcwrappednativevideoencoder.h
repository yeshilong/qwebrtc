#ifndef RTCWRAPPEDNATIVEVIDEOENCODER_H
#define RTCWRAPPEDNATIVEVIDEOENCODER_H

#include <QObject>

#include "rtcvideoencoder.h"

/**
 * @brief The RTCWrappedNativeVideoEncoder class.
 */
class RTCWrappedNativeVideoEncoder : public IRTCVideoEncoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCWrappedNativeVideoEncoder object.
     */
    explicit RTCWrappedNativeVideoEncoder(QObject *parent = nullptr);
};

#endif // RTCWRAPPEDNATIVEVIDEOENCODER_H
