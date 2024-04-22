#include "rtcframecryptor.h"

RTCFrameCryptor::RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpSender *sender,
                                 const QString &participantId, RTCCyrptorAlgorithm algorithm,
                                 RTCFrameCryptorKeyProvider *keyProvider, QObject *parent)
    : QObject{parent}
{
}

RTCFrameCryptor::RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpReceiver *receiver,
                                 const QString &participantId, RTCCyrptorAlgorithm algorithm,
                                 RTCFrameCryptorKeyProvider *keyProvider, QObject *parent)
    : QObject{parent}
{
}

bool RTCFrameCryptor::enabled() const
{
    return enabled_;
}

void RTCFrameCryptor::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

uint RTCFrameCryptor::keyIndex() const
{
    return keyIndex_;
}

void RTCFrameCryptor::setKeyIndex(uint index)
{
    keyIndex_ = index;
}

QString RTCFrameCryptor::participantId() const
{
    return participantId_;
}

void RTCFrameCryptor::onStateChanged(FrameCryptionState stateChanged)
{
    Q_UNUSED(stateChanged);
}
