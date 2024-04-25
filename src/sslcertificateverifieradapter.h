#ifndef SSLCERTIFICATEVERIFIERADAPTER_H
#define SSLCERTIFICATEVERIFIERADAPTER_H

#include <memory>

#include "rtcsslcertificateverifier.h"

#include "rtc_base/ssl_certificate.h"

namespace webrtc
{

std::unique_ptr<rtc::SSLCertificateVerifier> QtToNativeCertificateVerifier(
    IRTCSSLCertificateVerifier *qt_certificate_verifier);

} // namespace webrtc

#endif // SSLCERTIFICATEVERIFIERADAPTER_H
