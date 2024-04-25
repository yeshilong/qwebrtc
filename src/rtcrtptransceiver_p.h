#ifndef RTCRTPTRANSCEIVER_P_H
#define RTCRTPTRANSCEIVER_P_H

#include <QString>

#include "rtcrtptransceiver.h"

#include "api/rtp_transceiver_interface.h"

class RTCPeerConnectionFactory;
class RTCRtpTransceiverPrivate
{
  public:
    explicit RTCRtpTransceiverPrivate(
        RTCPeerConnectionFactory *factory,
        rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver);
    ~RTCRtpTransceiverPrivate();
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver() const;

    RTCPeerConnectionFactory *factory_;
    IRTCRtpSender *sender_;
    RTCRtpReceiver *receiver_;
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver_;
};

#endif // RTCRTPTRANSCEIVER_P_H
