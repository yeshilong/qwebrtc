#ifndef RTCFRAMECRYPTOR_H
#define RTCFRAMECRYPTOR_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCPeerConnectionFactory;
class RTCFrameCryptorKeyProvider;
class RTCRtpSender;
class RTCRtpReceiver;

/**
 * @brief The RTCFrameCryptor class represents a frame cryptor.
 */
class RTCFrameCryptor : public QObject
{
    Q_OBJECT

  public:
    explicit RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpSender *sender,
                             const QString &participantId, RTCCyrptorAlgorithm algorithm,
                             RTCFrameCryptorKeyProvider *keyProvider, QObject *parent = nullptr);
    explicit RTCFrameCryptor(RTCPeerConnectionFactory *factory, RTCRtpReceiver *receiver,
                             const QString &participantId, RTCCyrptorAlgorithm algorithm,
                             RTCFrameCryptorKeyProvider *keyProvider, QObject *parent = nullptr);

    bool enabled() const;
    void setEnabled(bool enabled);

    uint keyIndex() const;
    void setKeyIndex(uint index);

    QString participantId() const;

  Q_SIGNALS:
    void frameCryptorStateChanged(RTCFrameCryptor *frameCryptor, QString participantId,
                                  FrameCryptionState stateChanged);

  public Q_SLOTS:
    void onStateChanged(FrameCryptionState stateChanged);

  private:
    bool enabled_;
    uint keyIndex_;
    QString participantId_;
};

#endif // RTCFRAMECRYPTOR_H
