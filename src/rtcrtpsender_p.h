#ifndef RTCRTPSENDER_P_H
#define RTCRTPSENDER_P_H

#include <QString>

#include "api/scoped_refptr.h"
#include "api/rtp_sender_interface.h"
#include "api/crypto/frame_encryptor_interface.h"

class RTCPeerConnectionFactory;
class IRTCDtmfSender;
class RTCRtpSenderPrivate
{
  public:
    RTCRtpSenderPrivate(RTCPeerConnectionFactory *factory,
                        const rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender);
    rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender() const;
    rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frameEncryptor() const;
    void setFrameEncryptor(
        const rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frameEncryptor);

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender_;
    IRTCDtmfSender *dtmfSender_;
};

#endif // RTCRTPSENDER_P_H
