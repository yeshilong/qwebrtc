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
