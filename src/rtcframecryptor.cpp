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

#include "rtcframecryptor_p.h"

#include "rtcrtpsender.h"
#include "rtcrtpsender_p.h"
#include "rtcrtpreceiver_p.h"

namespace webrtc
{

RTCFrameCryptorDelegateAdapter::RTCFrameCryptorDelegateAdapter(
    std::shared_ptr<RTCFrameCryptor> frameCryptor)
    : frame_cryptor_(frameCryptor)
{
}

RTCFrameCryptorDelegateAdapter::~RTCFrameCryptorDelegateAdapter()
{
}

void RTCFrameCryptorDelegateAdapter::OnFrameCryptionStateChanged(const std::string participant_id,
                                                                 webrtc::FrameCryptionState state)
{
    auto frameCryptor = frame_cryptor_.lock();
    if (frameCryptor->delegate())
    {
        switch (state)
        {
        case FrameCryptionState::kNew:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kOk:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kEncryptionFailed:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kDecryptionFailed:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kMissingKey:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kKeyRatcheted:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        case FrameCryptionState::kInternalError:
            frameCryptor->delegate()->frameCryptor(frameCryptor.get(),
                                                   QString::fromStdString(participant_id),
                                                   static_cast<RTCFrameCryptionState>(state));
            break;
        }
    }
}

} // namespace webrtc

RTCFrameCryptorPrivate::RTCFrameCryptorPrivate(RTCPeerConnectionFactory *factory,
                                               RTCRtpSender *sender, const QString &participantId,
                                               RTCCyrptorAlgorithm algorithm,
                                               RTCFrameCryptorKeyProvider *keyProvider,
                                               QObject *parent)
{
    // participantId_ = participantId;
    // observer_ = rtc::make_ref_counted<webrtc::RTCFrameCryptorDelegateAdapter>(shared_from_this());
    // auto rtpSender = sender->nativeRtpSender();
    // auto mediaType = rtpSender->track()->kind() == "audio"
    //                      ? webrtc::FrameCryptorTransformer::MediaType::kAudioFrame
    //                      : webrtc::FrameCryptorTransformer::MediaType::kVideoFrame;
    // frameCryptorTransformer_ = rtc::scoped_refptr<webrtc::FrameCryptorTransformer>(
    //     sender_, participantId.toStdString(),
    //     static_cast<webrtc::FrameCryptorTransformer::Algorithm>(algorithm), keyProvider, observer_,
    //     webrtc::FrameCryptorTransformer::Direction::kEncrypt);
}

RTCFrameCryptorPrivate::RTCFrameCryptorPrivate(
    RTCPeerConnectionFactory *factory, RTCRtpReceiver *receiver, const QString &participantId,
    RTCCyrptorAlgorithm algorithm, RTCFrameCryptorKeyProvider *keyProvider, QObject *parent)
{
    // participantId_ = participantId;
    // observer_ = rtc::make_ref_counted<webrtc::RTCFrameCryptorDelegateAdapter>(shared_from_this());
    // auto rtpReceiver = receiver->nativeRtpReceiver();
    // auto mediaType = rtpReceiver->track()->kind() == "audio"
    //                      ? webrtc::FrameCryptorTransformer::MediaType::kAudioFrame
    //                      : webrtc::FrameCryptorTransformer::MediaType::kVideoFrame;
    // frameCryptorTransformer_ = rtc::scoped_refptr<webrtc::FrameCryptorTransformer>(
    //     receiver_, participantId.toStdString(),
    //     static_cast<webrtc::FrameCryptorTransformer::Algorithm>(algorithm), keyProvider, observer_,
    //     webrtc::FrameCryptorTransformer::Direction::kDecrypt);
}

RTCFrameCryptor::RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpSender *sender,
                                 const QString &participantId, RTCCyrptorAlgorithm algorithm,
                                 RTCFrameCryptorKeyProvider *keyProvider, QObject *parent)
    : QObject{parent}, d_ptr{new RTCFrameCryptorPrivate{factory, sender, participantId, algorithm,
                                                        keyProvider, this}}
{
}

RTCFrameCryptor::RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpReceiver *receiver,
                                 const QString &participantId, RTCCyrptorAlgorithm algorithm,
                                 RTCFrameCryptorKeyProvider *keyProvider, QObject *parent)
    : QObject{parent}, d_ptr{new RTCFrameCryptorPrivate{factory, receiver, participantId, algorithm,
                                                        keyProvider, this}}
{
}

bool RTCFrameCryptor::enabled() const
{
    Q_D(const RTCFrameCryptor);
    return d->frameCryptorTransformer_->enabled();
}

void RTCFrameCryptor::setEnabled(bool enabled)
{
    Q_D(RTCFrameCryptor);
    d->frameCryptorTransformer_->SetEnabled(enabled);
}

uint RTCFrameCryptor::keyIndex() const
{
    Q_D(const RTCFrameCryptor);
    return d->frameCryptorTransformer_->key_index();
}

void RTCFrameCryptor::setKeyIndex(uint index)
{
    Q_D(RTCFrameCryptor);
    d->frameCryptorTransformer_->SetKeyIndex(index);
}

QString RTCFrameCryptor::participantId() const
{
    Q_D(const RTCFrameCryptor);
    return d->participantId_;
}

RTCFrameCryptorDelegate *RTCFrameCryptor::delegate() const
{
    return delegate_;
}

void RTCFrameCryptor::setDelegate(RTCFrameCryptorDelegate *delegate)
{
    delegate_ = delegate;
}

void RTCFrameCryptor::onStateChanged(RTCFrameCryptionState stateChanged)
{
    Q_UNUSED(stateChanged);
}
