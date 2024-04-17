#include "rtciceserver.h"

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}
{
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}, username_{username}, credential_{credential}
{
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}, username_{username}, credential_{credential},
      tlsCertPolicy_{tlsCertPolicy}
{
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname, QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}, username_{username}, credential_{credential},
      tlsCertPolicy_{tlsCertPolicy}, hostname_{hostname}
{
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                           QVector<QString> tlsAlpnProtocols, QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}, username_{username}, credential_{credential},
      tlsCertPolicy_{tlsCertPolicy}, hostname_{hostname}, tlsAlpnProtocols_{tlsAlpnProtocols}
{
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                           QVector<QString> tlsAlpnProtocols, QVector<QString> tlsEllipticCurves,
                           QObject *parent)
    : QObject{parent}, urlStrings_{urlStrings}, username_{username}, credential_{credential},
      tlsCertPolicy_{tlsCertPolicy}, hostname_{hostname}, tlsAlpnProtocols_{tlsAlpnProtocols},
      tlsEllipticCurves_{tlsEllipticCurves}
{
}

QVector<QString> RTCIceServer::urlStrings() const
{
    return urlStrings_;
}

QString RTCIceServer::username() const
{
    return username_;
}

QString RTCIceServer::credential() const
{
    return credential_;
}

RTCTlsCertPolicy RTCIceServer::tlsCertPolicy() const
{
    return tlsCertPolicy_;
}

QString RTCIceServer::hostname() const
{
    return hostname_;
}

QVector<QString> RTCIceServer::tlsAlpnProtocols() const
{
    return tlsAlpnProtocols_;
}

QVector<QString> RTCIceServer::tlsEllipticCurves() const
{
    return tlsEllipticCurves_;
}
