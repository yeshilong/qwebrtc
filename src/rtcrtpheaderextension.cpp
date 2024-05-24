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

#include "rtcrtpheaderextension.h"
#include "rtcrtpheaderextension_p.h"

void RTCRtpHeaderExtensionPrivate::init(const webrtc::RtpExtension &nativeRtpExtension)
{
    uri_ = QString::fromStdString(nativeRtpExtension.uri);
    id_ = nativeRtpExtension.id;
    encrypted_ = nativeRtpExtension.encrypt;
}

RTCRtpHeaderExtensionPrivate::RTCRtpHeaderExtensionPrivate()
{
    webrtc::RtpExtension nativeRtpExtension;
    init(nativeRtpExtension);
}

RTCRtpHeaderExtensionPrivate::RTCRtpHeaderExtensionPrivate(
    const webrtc::RtpExtension &nativeRtpExtension)
{
    init(nativeRtpExtension);
}

webrtc::RtpExtension RTCRtpHeaderExtensionPrivate::nativeRtpExtension() const
{
    webrtc::RtpExtension nativeRtpExtension;
    nativeRtpExtension.uri = uri_.toStdString();
    nativeRtpExtension.id = id_;
    nativeRtpExtension.encrypt = encrypted_;
    return nativeRtpExtension;
}

RTCRtpHeaderExtension::RTCRtpHeaderExtension(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpHeaderExtensionPrivate}
{
}

RTCRtpHeaderExtension::RTCRtpHeaderExtension(RTCRtpHeaderExtensionPrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
}

QString RTCRtpHeaderExtension::uri() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->uri_;
}

int RTCRtpHeaderExtension::id() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->id_;
}

bool RTCRtpHeaderExtension::encrypted() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->encrypted_;
}
