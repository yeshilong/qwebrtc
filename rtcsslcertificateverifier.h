#ifndef RTCSSLCERTIFICATEVERIFIER_H
#define RTCSSLCERTIFICATEVERIFIER_H

#include <QObject>
#include <QByteArray>

/**
 * @brief The RTCSSLCertificateVerifier interface.
 */
class IRTCSSLCertificateVerifier
{
  public:
    /**
     * @brief Verify the certificate.
     * @param derCertificate The certificate to verify.
     * @return True if the certificate is verified, false otherwise.
     */
    virtual bool verify(QByteArray derCertificate) = 0;
};

#endif // RTCSSLCERTIFICATEVERIFIER_H
