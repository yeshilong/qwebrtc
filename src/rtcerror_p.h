#ifndef RTCERROR_P_H
#define RTCERROR_P_H

#include <QObject>

#include "rtcerror.h"

#include "api/rtc_error.h"

class RTCErrorPrivate
{
  public:
    explicit RTCErrorPrivate(const webrtc::RTCError &nativeError);
    webrtc::RTCError nativeError() const;

    webrtc::RTCError nativeError_;
};

#endif // RTCERROR_P_H
