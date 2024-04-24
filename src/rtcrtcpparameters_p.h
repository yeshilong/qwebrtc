#ifndef RTCRTCPPARAMETERS_P_H
#define RTCRTCPPARAMETERS_P_H

#include <QObject>

#include "api/rtp_parameters.h"

class RTCRtcpParametersPrivate
{
  public:
    explicit RTCRtcpParametersPrivate();
    RTCRtcpParametersPrivate(const webrtc::RtcpParameters &nativeRtcpParameters);
    webrtc::RtcpParameters nativeRtcpParameters() const;

    QString cName_;
    bool isReducedSize_;
};

#endif // RTCRTCPPARAMETERS_P_H
