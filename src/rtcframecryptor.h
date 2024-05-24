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
