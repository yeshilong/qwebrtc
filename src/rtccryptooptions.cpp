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

#include "rtccryptooptions.h"

RTCCryptoOptions::RTCCryptoOptions(QObject *parent) : QObject{parent}
{
}

RTCCryptoOptions::RTCCryptoOptions(bool srtpEnableGcmCryptoSuites,
                                   bool srtpEnableAes128Sha1_32CryptoCipher,
                                   bool srtpEnableEncryptedRtpHeaderExtensions,
                                   bool sframeRequireFrameEncryption)
    : srtpEnableGcmCryptoSuites_{srtpEnableGcmCryptoSuites},
      srtpEnableAes128Sha1_32CryptoCipher_{srtpEnableAes128Sha1_32CryptoCipher},
      srtpEnableEncryptedRtpHeaderExtensions_{srtpEnableEncryptedRtpHeaderExtensions},
      sframeRequireFrameEncryption_{sframeRequireFrameEncryption}
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
