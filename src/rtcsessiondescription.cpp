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

#include "rtcsessiondescription_p.h"

RTCSessionDescriptionPrivate::RTCSessionDescriptionPrivate(RTCSdpType type, QString sdp)
    : type_(type), sdp_(sdp)
{
}

RTCSessionDescriptionPrivate::RTCSessionDescriptionPrivate(
    const webrtc::SessionDescriptionInterface *nativeSessionDescription)
{
    Q_ASSERT(nativeSessionDescription);
    std::string sdp;
    nativeSessionDescription->ToString(&sdp);
    sdp_ = QString::fromStdString(sdp);
    type_ = static_cast<RTCSdpType>(nativeSessionDescription->GetType());
}

std::unique_ptr<webrtc::SessionDescriptionInterface> RTCSessionDescriptionPrivate::
    nativeSessionDescription() const
{
    webrtc::SdpParseError error;
    std::unique_ptr<webrtc::SessionDescriptionInterface> sessionDescription(
        webrtc::CreateSessionDescription(static_cast<webrtc::SdpType>(type_), sdp_.toStdString(),
                                         &error));

    if (!sessionDescription)
    {
        qFatal("Failed to create session description %s\n line: %s", error.description.c_str(),
               error.line.c_str());
    }

    return sessionDescription;
}

RTCSessionDescription::RTCSessionDescription(RTCSdpType type, QString sdp, QObject *parent)
    : QObject(parent), d_ptr(new RTCSessionDescriptionPrivate(type, sdp))
{
}

RTCSessionDescription::RTCSessionDescription(RTCSessionDescriptionPrivate &d, QObject *parent)
    : QObject(parent), d_ptr(&d)
{
}

RTCSdpType RTCSessionDescription::type() const
{
    Q_D(const RTCSessionDescription);
    return d->type_;
}

QString RTCSessionDescription::sdp() const
{
    Q_D(const RTCSessionDescription);
    return d->sdp_;
}
