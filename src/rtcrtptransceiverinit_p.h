#ifndef RTCRTPTRANSCEIVERINIT_P_H
#define RTCRTPTRANSCEIVERINIT_P_H

#include <QString>

#include "rtcrtptransceiverinit.h"

#include "api/rtp_transceiver_interface.h"

class RTCRtpTransceiverInitPrivate
{
  public:
    RTCRtpTransceiverInitPrivate();
    ~RTCRtpTransceiverInitPrivate();

    webrtc::RtpTransceiverInit nativeRtpTransceiverInit() const;

    RTCRtpTransceiverDirection direction_;
    QVector<QString> streamIds_;
    QVector<RTCRtpEncodingParameters *> sendEncodings_;
};

#endif // RTCRTPTRANSCEIVERINIT_P_H
