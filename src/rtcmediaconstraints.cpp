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

#include "rtcmediaconstraints_p.h"

RTCMediaConstraintsPrivate::RTCMediaConstraintsPrivate(QMap<QString, QString> mandatory,
                                                       QMap<QString, QString> optional)
    : mandatory_{mandatory}, optional_{optional}
{
}

std::unique_ptr<webrtc::MediaConstraints> RTCMediaConstraintsPrivate::nativeMediaConstraints()
{
    webrtc::MediaConstraints::Constraints nativeMandatory =
        nativeMediaConstraintsForConstraints(mandatory_);
    webrtc::MediaConstraints::Constraints nativeOptional =
        nativeMediaConstraintsForConstraints(optional_);

    return std::make_unique<webrtc::MediaConstraints>(nativeMandatory, nativeOptional);
}

webrtc::MediaConstraints::Constraints RTCMediaConstraintsPrivate::
    nativeMediaConstraintsForConstraints(QMap<QString, QString> constraints)
{
    webrtc::MediaConstraints::Constraints nativeConstraints;
    for (auto it = constraints.begin(); it != constraints.end(); ++it)
    {
        nativeConstraints.push_back({it.key().toStdString(), it.value().toStdString()});
    }
    return nativeConstraints;
}

RTCMediaConstraints::RTCMediaConstraints(QMap<QString, QString> mandatory,
                                         QMap<QString, QString> optional, QObject *parent)
    : QObject{parent}, d_ptr{new RTCMediaConstraintsPrivate{mandatory, optional}}
{
}

QString RTCMediaConstraints::RTCMediaConstraintsAudioNetworkAdaptorConfig()
{
    return webrtc::MediaConstraints::kAudioNetworkAdaptorConfig;
}

QString RTCMediaConstraints::RTCMediaConstraintsIceRestart()
{
    return webrtc::MediaConstraints::kIceRestart;
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveAudio()
{
    return webrtc::MediaConstraints::kOfferToReceiveAudio;
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveVideo()
{
    return webrtc::MediaConstraints::kOfferToReceiveVideo;
}

QString RTCMediaConstraints::RTCMediaConstraintsVoiceActivityDetection()
{
    return webrtc::MediaConstraints::kVoiceActivityDetection;
}

QString RTCMediaConstraints::RTCMediaConstraintsValueTrue()
{
    return webrtc::MediaConstraints::kValueTrue;
}

QString RTCMediaConstraints::RTCMediaConstraintsValueFalse()
{
    return webrtc::MediaConstraints::kValueFalse;
}
