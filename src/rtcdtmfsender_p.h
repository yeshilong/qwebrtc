#ifndef RTCDTMFSENDER_P_H
#define RTCDTMFSENDER_P_H

#include "rtcdtmfsender.h"

#include "api/dtmf_sender_interface.h"

class RTCDtmfSenderPrivate
{
  public:
    explicit RTCDtmfSenderPrivate(rtc::scoped_refptr<webrtc::DtmfSenderInterface> dtmfSender);
    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender() const;

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender_;
};

#endif // RTCDTMFSENDER_P_H
