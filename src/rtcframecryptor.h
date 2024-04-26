#ifndef RTCFRAMECRYPTOR_H
#define RTCFRAMECRYPTOR_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCPeerConnectionFactory;
class RTCFrameCryptorKeyProvider;
class RTCRtpSender;
class RTCRtpReceiver;
class RTCFrameCryptor;

class RTCFrameCryptorDelegate
{
  public:
    virtual void frameCryptor(RTCFrameCryptor *frameCryptor, const QString &participantId,
                              RTCFrameCryptionState stateChanged) = 0;
};

class RTCFrameCryptorPrivate;
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

    RTCFrameCryptorDelegate *delegate() const;
    void setDelegate(RTCFrameCryptorDelegate *delegate);

  Q_SIGNALS:
    void frameCryptorStateChanged(RTCFrameCryptor *frameCryptor, QString participantId,
                                  RTCFrameCryptionState stateChanged);

  public Q_SLOTS:
    void onStateChanged(RTCFrameCryptionState stateChanged);

  private:
    RTCFrameCryptorPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCFrameCryptor)

    RTCFrameCryptorDelegate *delegate_;
};

#endif // RTCFRAMECRYPTOR_H
