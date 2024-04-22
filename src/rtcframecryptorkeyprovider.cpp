#include "rtcframecryptorkeyprovider.h"

RTCFrameCryptorKeyProvider::RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize,
                                                       bool sharedKeyMode,
                                                       QByteArray uncryptedMagicBytes,
                                                       QObject *parent)
    : QObject{parent}
{
}

RTCFrameCryptorKeyProvider::RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize,
                                                       bool sharedKeyMode,
                                                       QByteArray uncryptedMagicBytes,
                                                       int failureTolerance, QObject *parent)
    : QObject{parent}
{
}

void RTCFrameCryptorKeyProvider::setSharedKey(QByteArray key, int index)
{
}

QByteArray RTCFrameCryptorKeyProvider::ratchetSharedKey(int index)
{
    return QByteArray{};
}

QByteArray RTCFrameCryptorKeyProvider::exportSharedKey(int index)
{
    return QByteArray{};
}

void RTCFrameCryptorKeyProvider::setKey(QByteArray key, int index, QString participantId)
{
}

QByteArray RTCFrameCryptorKeyProvider::ratchetKey(QString participantId, int index)
{
    return QByteArray{};
}

QByteArray RTCFrameCryptorKeyProvider::exportKey(QString participantId, int index)
{
    return QByteArray{};
}

void RTCFrameCryptorKeyProvider::setSifTrailer(QByteArray trailer)
{
}
