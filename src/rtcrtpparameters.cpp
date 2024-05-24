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

#include "rtcrtpparameters.h"
#include "rtcrtpparameters_p.h"
#include "rtcrtcpparameters_p.h"
#include "rtcrtpcodecparameters_p.h"
#include "rtcrtpencodingparameters_p.h"
#include "rtcrtpheaderextension_p.h"

void RTCRtpParametersPrivate::init(const webrtc::RtpParameters &nativeRtpParameters)
{
    transactionId_ = QString::fromStdString(nativeRtpParameters.transaction_id);
    rtcp_ = new RTCRtcpParameters(new RTCRtcpParametersPrivate(nativeRtpParameters.rtcp));
    for (const auto &headerExtension : nativeRtpParameters.header_extensions)
    {
        headerExtensions_.push_back(
            new RTCRtpHeaderExtension(new RTCRtpHeaderExtensionPrivate(headerExtension)));
    }

    for (const auto &encoding : nativeRtpParameters.encodings)
    {
        encodings_.push_back(
            new RTCRtpEncodingParameters(new RTCRtpEncodingParametersPrivate(encoding)));
    }

    for (const auto &codec : nativeRtpParameters.codecs)
    {
        codecs_.push_back(new RTCRtpCodecParameters(new RTCRtpCodecParametersPrivate(codec)));
    }

    degradationPreference_ = QVariant::fromValue(nativeRtpParameters.degradation_preference);
}

RTCRtpParametersPrivate::RTCRtpParametersPrivate()
{
    webrtc::RtpParameters nativeParameters;
    init(nativeParameters);
}

RTCRtpParametersPrivate::RTCRtpParametersPrivate(const webrtc::RtpParameters &nativeRtpParameters)
{
    init(nativeRtpParameters);
}

webrtc::RtpParameters RTCRtpParametersPrivate::nativeRtpParameters() const
{
    webrtc::RtpParameters nativeParameters;
    nativeParameters.transaction_id = transactionId_.toStdString();
    nativeParameters.rtcp = rtcp_->d_ptr->nativeRtcpParameters();
    for (const auto &headerExtension : headerExtensions_)
    {
        nativeParameters.header_extensions.push_back(headerExtension->d_ptr->nativeRtpExtension());
    }
    for (const auto &encoding : encodings_)
    {
        nativeParameters.encodings.push_back(encoding->d_ptr->nativeRtpEncodingParameters());
    }
    for (const auto &codec : codecs_)
    {
        nativeParameters.codecs.push_back(codec->d_ptr->nativeRtpCodecParameters());
    }
    nativeParameters.degradation_preference =
        degradationPreference_.value<webrtc::DegradationPreference>();
    return nativeParameters;
}

RTCRtpParameters::RTCRtpParameters(QObject *parent) : QObject{parent}
{
}

RTCRtpParameters::RTCRtpParameters(RTCRtpParametersPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCRtpParameters::transactionId() const
{
    Q_D(const RTCRtpParameters);
    return d->transactionId_;
}

void RTCRtpParameters::setTransactionId(const QString &id)
{
    Q_D(RTCRtpParameters);
    d->transactionId_ = id;
}

RTCRtcpParameters *RTCRtpParameters::rtcp() const
{
    Q_D(const RTCRtpParameters);
    return d->rtcp_;
}

QVector<RTCRtpHeaderExtension *> RTCRtpParameters::headerExtensions() const
{
    Q_D(const RTCRtpParameters);
    return d->headerExtensions_;
}

QVector<RTCRtpEncodingParameters *> RTCRtpParameters::encodings() const
{
    Q_D(const RTCRtpParameters);
    return d->encodings_;
}

void RTCRtpParameters::setEncodings(const QVector<RTCRtpEncodingParameters *> &encodings)
{
    Q_D(RTCRtpParameters);
    d->encodings_ = encodings;
}

QVector<RTCRtpCodecParameters *> RTCRtpParameters::codecs() const
{
    Q_D(const RTCRtpParameters);
    return d->codecs_;
}

void RTCRtpParameters::setCodecs(const QVector<RTCRtpCodecParameters *> &codecs)
{
    Q_D(RTCRtpParameters);
    d->codecs_ = codecs;
}

QVariant RTCRtpParameters::degradationPreference() const
{
    Q_D(const RTCRtpParameters);
    return d->degradationPreference_;
}

void RTCRtpParameters::setDegradationPreference(const QVariant &preference)
{
    Q_D(RTCRtpParameters);
    d->degradationPreference_ = preference;
}
