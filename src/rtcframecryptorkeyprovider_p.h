#ifndef RTCFRAMECRYPTORKEYPROVIDER_P_H
#define RTCFRAMECRYPTORKEYPROVIDER_P_H

#include <QByteArray>

#include <memory>

#include "rtc_base/ref_count.h"
#include "api/crypto/frame_crypto_transformer.h"

class RTCFrameCryptorKeyProviderPrivate
{
  public:
    explicit RTCFrameCryptorKeyProviderPrivate();
    rtc::scoped_refptr<webrtc::KeyProvider> nativeKeyProvider() const;

    rtc::scoped_refptr<webrtc::DefaultKeyProviderImpl> nativeKeyProvider_;
};

#endif // RTCFRAMECRYPTORKEYPROVIDER_P_H
