#ifndef RTCWRAPPEDNATIVEVIDEODECODER_H
#define RTCWRAPPEDNATIVEVIDEODECODER_H

#include <QObject>

#include "rtcvideodecoder.h"

/**
 * @brief The RTCWrappedNativeVideoDecoder class.
 */
class RTCWrappedNativeVideoDecoder : public IRTCVideoDecoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCWrappedNativeVideoDecoder object.
     */
    explicit RTCWrappedNativeVideoDecoder(QObject *parent = nullptr);
};

#endif // RTCWRAPPEDNATIVEVIDEODECODER_H
