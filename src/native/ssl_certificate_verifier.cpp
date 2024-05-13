#include "ssl_certificate_verifier.h"

class SSLCertificateVerifierAdapter final : public rtc::SSLCertificateVerifier {
 public:
  explicit SSLCertificateVerifierAdapter(IRTCSSLCertificateVerifier* qt_certificate_verifier)
      : objc_certificate_verifier_(qt_certificate_verifier) {
    Q_ASSERT(objc_certificate_verifier_ != nullptr);
  }

  bool Verify(const rtc::SSLCertificate& certificate) override {
    rtc::Buffer der_buffer;
    certificate.ToDER(&der_buffer);
    QByteArray serialized_certificate(reinterpret_cast<const char*>(der_buffer.data()),
                                      der_buffer.size());
    return objc_certificate_verifier_->verify(serialized_certificate);
  }

 private:
  IRTCSSLCertificateVerifier* objc_certificate_verifier_;
};

namespace webrtc {

std::unique_ptr<rtc::SSLCertificateVerifier> ObjCToNativeCertificateVerifier(
    IRTCSSLCertificateVerifier* qt_certificate_verifier) {
  return std::make_unique<SSLCertificateVerifierAdapter>(qt_certificate_verifier);
}

}  // namespace webrtc
