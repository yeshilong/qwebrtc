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
    RTCIceServerPrivate(webrtc::PeerConnectionInterface::IceServer nativeServer);
    webrtc::PeerConnectionInterface::IceServer getNativeServer() const;

    QVector<QString> urlStrings_;
    QString username_;
    QString credential_;
    RTCTlsCertPolicy tlsCertPolicy_;
    QString hostname_;
    QVector<QString> tlsAlpnProtocols_;
    QVector<QString> tlsEllipticCurves_;
};

#endif // RTCICESERVER_P_H
