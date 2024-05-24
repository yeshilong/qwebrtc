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

#ifndef RTCICESERVER_P_H
#define RTCICESERVER_P_H

#include <QString>
#include <QVector>

#include "api/peer_connection_interface.h"

#include "rtctypes.h"

class RTCIceServerPrivate
{
  public:
    RTCIceServerPrivate();
    RTCIceServerPrivate(webrtc::PeerConnectionInterface::IceServer nativeIceServer);
    webrtc::PeerConnectionInterface::IceServer nativeIceServer() const;

    QVector<QString> urlStrings_;
    QString username_;
    QString credential_;
    RTCTlsCertPolicy tlsCertPolicy_;
    QString hostname_;
    QVector<QString> tlsAlpnProtocols_;
    QVector<QString> tlsEllipticCurves_;
};

#endif // RTCICESERVER_P_H
