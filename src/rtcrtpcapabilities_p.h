#ifndef RTCRTPCAPABILITIES_P_H
#define RTCRTPCAPABILITIES_P_H

#include <QString>

#include "api/rtp_parameters.h"

class RTCRtpCapabilitiesPrivate
{
  public:
    RTCRtpCapabilitiesPrivate();
    RTCRtpCapabilitiesPrivate(const webrtc::RtpCapabilities &nativeRtpCapabilities);
    void init(const webrtc::RtpCapabilities &nativeRtpCapabilities);

    webrtc::RtpCapabilities nativeRtpCapabilities_;
};

#endif // RTCRTPCAPABILITIES_P_H
