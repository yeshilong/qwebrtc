#ifndef RTCDTMFSENDER_P_H
#define RTCDTMFSENDER_P_H

#include "api/dtmf_sender_interface.h"

class RTCDtmfSenderPrivate
{
  public:
    explicit RTCDtmfSenderPrivate(webrtc::DtmfSenderInterface *dtmfSender)
        : nativeDtmfSender{dtmfSender}
    {
    }

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> getNativeDtmfSender() const
    {
        return nativeDtmfSender;
    }

    rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender;
};

#endif // RTCDTMFSENDER_P_H
