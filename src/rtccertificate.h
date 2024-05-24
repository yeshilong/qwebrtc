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

#ifndef RTCCERTIFICATE_H
#define RTCCERTIFICATE_H

#include "qwebrtcglobal.h"

#include <QObject>
#include <QString>
#include <QMap>

/**
 * @brief The RTCCertificate class represents a certificate with a private key and a public key.
 */
class QWEBRTC_EXPORT RTCCertificate : public QObject
{
    Q_OBJECT
  public:
    explicit RTCCertificate(QObject *parent = nullptr);
    RTCCertificate(const QString &privateKey, const QString &certificate,
                   QObject *parent = nullptr);

    /**
     * @brief Returns the private key in PEM.
     */
    QString privateKey() const;

    /**
     * @brief Returns the public key in an x509 cert encoded in PEM.
     */
    QString certificate() const;

    /**
     * @brief Generates a new certificate for 're' use.
     * Optional dictionary of parameters. Defaults to KeyType ECDSA if none are provided.
     * - name: "ECDSA" or "RSASSA-PKCS1-v1_5"
     */
    static RTCCertificate *generateCertificateWithParams(const QMap<QString, QString> &params);

  private:
    QString privateKey_;
    QString certificate_;
};

#endif // RTCCERTIFICATE_H
