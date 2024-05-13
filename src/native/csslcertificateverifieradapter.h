#ifndef SSLCERTIFICATEVERIFIERADAPTER_H
#define SSLCERTIFICATEVERIFIERADAPTER_H

#include <memory>

#include "rtc_base/ssl_certificate.h"
#include "rtcsslcertificateverifier.h"

namespace webrtc {

std::unique_ptr<rtc::SSLCertificateVerifier> CToNativeCertificateVerifier(
    IRTCSSLCertificateVerifier* qt_certificate_verifier);

}  // namespace webrtc

#endif  // SSLCERTIFICATEVERIFIERADAPTER_H
