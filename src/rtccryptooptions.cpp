#include "rtccryptooptions.h"

RTCCryptoOptions::RTCCryptoOptions(QObject *parent) : QObject{parent}
{
}

bool RTCCryptoOptions::sframeRequireFrameEncryption() const
{
    return sframeRequireFrameEncryption_;
}

void RTCCryptoOptions::setSframeRequireFrameEncryption(bool sframeRequireFrameEncryption)
{
    sframeRequireFrameEncryption_ = sframeRequireFrameEncryption;
}

bool RTCCryptoOptions::srtpEnableEncryptedRtpHeaderExtensions() const
{
    return srtpEnableEncryptedRtpHeaderExtensions_;
}

void RTCCryptoOptions::setSrtpEnableEncryptedRtpHeaderExtensions(
    bool srtpEnableEncryptedRtpHeaderExtensions)
{
    srtpEnableEncryptedRtpHeaderExtensions_ = srtpEnableEncryptedRtpHeaderExtensions;
}

bool RTCCryptoOptions::srtpEnableAes128Sha1_32CryptoCipher() const
{
    return srtpEnableAes128Sha1_32CryptoCipher_;
}

void RTCCryptoOptions::setSrtpEnableAes128Sha1_32CryptoCipher(
    bool srtpEnableAes128Sha1_32CryptoCipher)
{
    srtpEnableAes128Sha1_32CryptoCipher_ = srtpEnableAes128Sha1_32CryptoCipher;
}

bool RTCCryptoOptions::srtpEnableGcmCryptoSuites() const
{
    return srtpEnableGcmCryptoSuites_;
}

void RTCCryptoOptions::setSrtpEnableGcmCryptoSuites(bool srtpEnableGcmCryptoSuites)
{
    srtpEnableGcmCryptoSuites_ = srtpEnableGcmCryptoSuites;
}
