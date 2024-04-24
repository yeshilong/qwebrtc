#ifndef RTCRTPHEADEREXTENSION_P_H
#define RTCRTPHEADEREXTENSION_P_H

#include <QString>

#include "api/rtp_parameters.h"

class RTCRtpHeaderExtensionPrivate
{
  public:
    RTCRtpHeaderExtensionPrivate();
    RTCRtpHeaderExtensionPrivate(const webrtc::RtpExtension &nativeRtpExtension);
    void init(const webrtc::RtpExtension &nativeRtpExtension);
    webrtc::RtpExtension nativeRtpExtension() const;

    QString uri_;
    int id_;
    bool encrypted_;
};

#endif // RTCRTPHEADEREXTENSION_P_H
