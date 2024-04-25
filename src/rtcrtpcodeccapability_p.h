#ifndef RTCRTPCODECCAPABILITY_P_H
#define RTCRTPCODECCAPABILITY_P_H

#include <QString>

#include "api/rtp_parameters.h"

class RTCRtpCodecCapabilityPrivate
{
  public:
    RTCRtpCodecCapabilityPrivate();
    RTCRtpCodecCapabilityPrivate(const webrtc::RtpCodecCapability &nativeRtpCodecCapability);
    void init(const webrtc::RtpCodecCapability &nativeRtpCodecCapability);
    webrtc::RtpCodecCapability nativeRtpCodecCapability() const;

    webrtc::RtpCodecCapability nativeRtpCodecCapability_;
};

#endif // RTCRTPCODECCAPABILITY_P_H
