#ifndef RTCDTMFSENDER_P_H
#define RTCDTMFSENDER_P_H

#include "api/dtmf_sender_interface.h"

class RTCDtmfSenderPrivate
{
  public:
    explicit RTCDtmfSenderPrivate(webrtc::DtmfSenderInterface *dtmfSender)
        : nativeDtmfSender_{dtmfSender}
    {
    }

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender() const
    {
        return nativeDtmfSender_;
    }

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender_;
};

#endif // RTCDTMFSENDER_P_H
