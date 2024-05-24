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

#include "rtcicecandidateerrorevent.h"

RTCIceCandidateErrorEvent::RTCIceCandidateErrorEvent(QObject *parent) : QObject{parent}
{
}

RTCIceCandidateErrorEvent::RTCIceCandidateErrorEvent(const QString &address, int port,
                                                     const QString &url, int errorCode,
                                                     const QString &errorText, QObject *parent)
    : QObject{parent}, address_{address}, port_{port}, url_{url}, errorCode_{errorCode},
      errorText_{errorText}
{
}

QString RTCIceCandidateErrorEvent::address() const
{
    return address_;
}

int RTCIceCandidateErrorEvent::port() const
{
    return port_;
}

QString RTCIceCandidateErrorEvent::url() const
{
    return url_;
}

int RTCIceCandidateErrorEvent::errorCode() const
{
    return errorCode_;
}

QString RTCIceCandidateErrorEvent::errorText() const
{
    return errorText_;
}
