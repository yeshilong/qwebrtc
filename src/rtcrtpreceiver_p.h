#ifndef RTCRTPRECEIVER_P_H
#define RTCRTPRECEIVER_P_H

#include "api/scoped_refptr.h"
#include "api/rtp_receiver_interface.h"
#include "api/crypto/frame_decryptor_interface.h"

#include "rtcrtpreceiver.h"

namespace webrtc
{

class RtpReceiverDelegateAdapter : public RtpReceiverObserverInterface
{
  public:
    RtpReceiverDelegateAdapter(std::shared_ptr<RTCRtpReceiver> receiver);

    void OnFirstPacketReceived(cricket::MediaType media_type) override;

  private:
    std::weak_ptr<RTCRtpReceiver> receiver_;
};

} // namespace webrtc

class RTCPeerConnectionFactory;
class RTCRtpReceiverPrivate
{
  public:
    RTCRtpReceiverPrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver);
    rtc::scoped_refptr<webrtc::RtpReceiverInterface> nativeRtpReceiver() const;
    void setFrameDecryptor(
        const rtc::scoped_refptr<webrtc::FrameDecryptorInterface> frameDecryptor);

    RTCPeerConnectionFactory *factory_;
    rtc::scoped_refptr<webrtc::RtpReceiverInterface> nativeRtpReceiver_;
    std::unique_ptr<webrtc::RtpReceiverDelegateAdapter> observer_;
};

#endif // RTCRTPRECEIVER_P_H
