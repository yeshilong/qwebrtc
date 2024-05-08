#include "csslcertificateverifieradapter.h"

class CSslCertificateVerifierAdapter final : public rtc::SSLCertificateVerifier
{
  public:
    explicit CSslCertificateVerifierAdapter(IRTCSSLCertificateVerifier *qt_certificate_verifier)
        : qt_certificate_verifier_(qt_certificate_verifier)
    {
        Q_ASSERT(qt_certificate_verifier_ != nullptr);
    }

    bool Verify(const rtc::SSLCertificate &certificate) override
    {
        rtc::Buffer der_buffer;
        certificate.ToDER(&der_buffer);
        QByteArray serialized_certificate(reinterpret_cast<const char *>(der_buffer.data()),
                                          der_buffer.size());
        return qt_certificate_verifier_->verify(serialized_certificate);
    }

  private:
    IRTCSSLCertificateVerifier *qt_certificate_verifier_;
};

namespace webrtc
{

std::unique_ptr<rtc::SSLCertificateVerifier> CToNativeCertificateVerifier(
    IRTCSSLCertificateVerifier *qt_certificate_verifier)
{
    return std::make_unique<CSslCertificateVerifierAdapter>(qt_certificate_verifier);
}

} // namespace webrtc
