// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
