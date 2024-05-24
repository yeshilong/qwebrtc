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

#ifndef RTCCRYPTOOPTIONS_H
#define RTCCRYPTOOPTIONS_H

#include <QObject>

/**
 * @brief Represents the configuration options for WebRTC encryption.
 */
class RTCCryptoOptions : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Default constructor.
     */
    RTCCryptoOptions(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCCryptoOptions class with all options explicitly set.
     * @param srtpEnableGcmCryptoSuites Enables GCM crypto suites.
     * @param srtpEnableAes128Sha1_32CryptoCipher Enables the (potentially insecure) kSrtpAes128CmSha1_32 crypto cipher.
     * @param srtpEnableEncryptedRtpHeaderExtensions Enables encrypted RTP header extensions.
     * @param sframeRequireFrameEncryption Requires frame encryption for senders and decryption for receivers.
     */
    RTCCryptoOptions(bool srtpEnableGcmCryptoSuites, bool srtpEnableAes128Sha1_32CryptoCipher,
                     bool srtpEnableEncryptedRtpHeaderExtensions,
                     bool sframeRequireFrameEncryption);

    /**
     * @brief Gets whether GCM crypto suites are enabled.
     * @return True if GCM crypto suites are enabled, false otherwise.
     */
    bool srtpEnableGcmCryptoSuites() const;

    /**
     * @brief Sets whether to enable GCM crypto suites.
     * @param value True to enable GCM crypto suites, false to disable them.
     */
    void setSrtpEnableGcmCryptoSuites(bool value);

    /**
     * @brief Gets whether the (potentially insecure) kSrtpAes128CmSha1_32 crypto cipher is enabled.
     * @return True if the kSrtpAes128CmSha1_32 crypto cipher is enabled, false otherwise.
     */
    bool srtpEnableAes128Sha1_32CryptoCipher() const;

    /**
     * @brief Sets whether to enable the (potentially insecure) kSrtpAes128CmSha1_32 crypto cipher.
     * @param value True to enable the kSrtpAes128CmSha1_32 crypto cipher, false to disable it.
     */
    void setSrtpEnableAes128Sha1_32CryptoCipher(bool value);

    /**
     * @brief Gets whether encrypted RTP header extensions are enabled.
     * @return True if encrypted RTP header extensions are enabled, false otherwise.
     */
    bool srtpEnableEncryptedRtpHeaderExtensions() const;

    /**
     * @brief Sets whether to enable encrypted RTP header extensions.
     * @param value True to enable encrypted RTP header extensions, false to disable them.
     */
    void setSrtpEnableEncryptedRtpHeaderExtensions(bool value);

    /**
     * @brief Gets whether frame encryption is required for senders and decryption is required for receivers.
     * @return True if frame encryption is required for senders and decryption is required for receivers, false otherwise.
     */
    bool sframeRequireFrameEncryption() const;

    /**
     * @brief Sets whether to require frame encryption for senders and decryption for receivers.
     * @param value True to require frame encryption for senders and decryption for receivers, false otherwise.
     */
    void setSframeRequireFrameEncryption(bool value);

  private:
    bool srtpEnableGcmCryptoSuites_;
    bool srtpEnableAes128Sha1_32CryptoCipher_;
    bool srtpEnableEncryptedRtpHeaderExtensions_;
    bool sframeRequireFrameEncryption_;
};

#endif // RTCCRYPTOOPTIONS_H
