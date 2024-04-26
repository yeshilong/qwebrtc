#ifndef RTCFRAMECRYPTOR_P_H
#define RTCFRAMECRYPTOR_P_H

#include "rtcframecryptor.h"

#include <memory>

#include "api/crypto/frame_crypto_transformer.h"
#include "api/rtp_receiver_interface.h"
#include "api/rtp_sender_interface.h"

namespace webrtc
{

class RTCFrameCryptorDelegateAdapter : public FrameCryptorTransformerObserver
{
  public:
    RTCFrameCryptorDelegateAdapter(std::shared_ptr<RTCFrameCryptor> frameCryptor);
    ~RTCFrameCryptorDelegateAdapter() override;

    void OnFrameCryptionStateChanged(const std::string participant_id,
                                     FrameCryptionState error) override;

  private:
    std::weak_ptr<RTCFrameCryptor> frame_cryptor_;
};

} // namespace webrtc

class RTCFrameCryptorPrivate
{
  public:
    RTCFrameCryptorPrivate(RTCPeerConnectionFactory *factory, RTCRtpSender *sender,
                           const QString &participantId, RTCCyrptorAlgorithm algorithm,
                           RTCFrameCryptorKeyProvider *keyProvider, QObject *parent);
    RTCFrameCryptorPrivate(RTCPeerConnectionFactory *factory, RTCRtpReceiver *receiver,
                           const QString &participantId, RTCCyrptorAlgorithm algorithm,
                           RTCFrameCryptorKeyProvider *keyProvider, QObject *parent);

    webrtc::RtpSenderInterface *sender_;
    webrtc::RtpReceiverInterface *receiver_;
    QString participantId_;
    std::shared_ptr<webrtc::RTCFrameCryptorDelegateAdapter> observer_;
    std::unique_ptr<webrtc::FrameCryptorTransformer> frameCryptorTransformer_;
};

#endif // RTCFRAMECRYPTOR_P_H
