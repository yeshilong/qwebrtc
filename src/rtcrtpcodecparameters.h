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

#ifndef RTCRTPCODECPARAMETERS_H
#define RTCRTPCODECPARAMETERS_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>

class RTCRtpCodecParametersPrivate;
/**
 * @brief The RTCRtpCodecParameters class.
 */
class RTCRtpCodecParameters : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpCodecParameters object.
     */
    explicit RTCRtpCodecParameters(QObject *parent = nullptr);

    // Codec names
    static QString RTCRtxCodecName();
    static QString RTCRedCodecName();
    static QString RTCUlpfecCodecName();
    static QString RTCFlexfecCodecName();
    static QString RTCOpusCodecName();
    static QString RTCIsacCodecName();
    static QString RTCL16CodecName();
    static QString RTCG722CodecName();
    static QString RTCIlbcCodecName();
    static QString RTCPcmuCodecName();
    static QString RTCPcmaCodecName();
    static QString RTCDtmfCodecName();
    static QString RTCComfortNoiseCodecName();
    static QString RTCVp8CodecName();
    static QString RTCVp9CodecName();
    static QString RTCH264CodecName();
    static QString RTCAv1CodecName();

    /**
     * @brief Gets the RTP payload type.
     * @return The RTP payload type.
     */
    int payloadType() const;

    /**
     * @brief Sets the RTP payload type.
     * @param payloadType The RTP payload type.
     */
    void setPayloadType(int payloadType);

    /**
     * @brief Gets the codec MIME subtype.
     * @return The codec MIME subtype.
     */
    QString name() const;

    /**
     * @brief Gets the media type of this codec.
     * @return The media type of this codec.
     */
    QString kind() const;

    /**
     * @brief Gets the codec clock rate expressed in Hertz.
     * @return The codec clock rate.
     */
    QVariant clockRate() const;

    /**
     * @brief Gets the number of channels.
     * @return The number of channels.
     */
    QVariant numChannels() const;

    /**
     * @brief Gets the "format specific parameters" field from the "a=fmtp" line in the SDP.
     * @return The "format specific parameters".
     */
    QMap<QString, QString> parameters() const;

  protected:
    RTCRtpCodecParameters(RTCRtpCodecParametersPrivate *d, QObject *parent = nullptr);

  private:
    friend class RTCRtpParametersPrivate;
    friend class RTCRtpParameters;

    RTCRtpCodecParametersPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpCodecParameters)
};

#endif // RTCRTPCODECPARAMETERS_H
