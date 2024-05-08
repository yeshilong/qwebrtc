#include "rtciceserver.h"
#include "rtciceserver_p.h"

// MARK: - Private

RTCIceServerPrivate::RTCIceServerPrivate()
{
    urlStrings_ = QVector<QString>();
    username_ = QString();
    credential_ = QString();
    tlsCertPolicy_ = RTCTlsCertPolicy::TlsCertPolicySecure;
    hostname_ = QString();
    tlsAlpnProtocols_ = QVector<QString>();
    tlsEllipticCurves_ = QVector<QString>();
}

RTCIceServerPrivate::RTCIceServerPrivate(webrtc::PeerConnectionInterface::IceServer nativeIceServer)
{
    username_ = QString::fromStdString(nativeIceServer.username);
    credential_ = QString::fromStdString(nativeIceServer.password);
    hostname_ = QString::fromStdString(nativeIceServer.hostname);

    for (const auto &protocol : nativeIceServer.tls_alpn_protocols)
    {
        tlsAlpnProtocols_.append(QString::fromStdString(protocol));
    }

    for (const auto &curve : nativeIceServer.tls_elliptic_curves)
    {
        tlsEllipticCurves_.append(QString::fromStdString(curve));
    }

    for (const auto &url : nativeIceServer.urls)
    {
        urlStrings_.append(QString::fromStdString(url));
    }

    tlsCertPolicy_ = static_cast<RTCTlsCertPolicy>(nativeIceServer.tls_cert_policy);
}

webrtc::PeerConnectionInterface::IceServer RTCIceServerPrivate::nativeIceServer() const
{
    webrtc::PeerConnectionInterface::IceServer iceServer;
    iceServer.username = username_.toStdString();
    iceServer.password = credential_.toStdString();
    iceServer.hostname = hostname_.toStdString();

    for (const auto &protocol : tlsAlpnProtocols_)
    {
        iceServer.tls_alpn_protocols.push_back(protocol.toStdString());
    }

    for (const auto &curve : tlsEllipticCurves_)
    {
        iceServer.tls_elliptic_curves.push_back(curve.toStdString());
    }

    for (const auto &url : urlStrings_)
    {
        iceServer.urls.push_back(url.toStdString());
    }

    iceServer.tls_cert_policy =
        static_cast<webrtc::PeerConnectionInterface::TlsCertPolicy>(tlsCertPolicy_);

    return iceServer;
}

void RTCIceServer::init(QVector<QString> urlStrings, QString username, QString credential,
                        RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                        QVector<QString> tlsAlpnProtocols, QVector<QString> tlsEllipticCurves)

{
    d_ptr = new RTCIceServerPrivate();
    d_ptr->urlStrings_ = urlStrings;
    d_ptr->username_ = username;
    d_ptr->credential_ = credential;
    d_ptr->tlsCertPolicy_ = tlsCertPolicy;
    d_ptr->hostname_ = hostname;
    d_ptr->tlsAlpnProtocols_ = tlsAlpnProtocols;
    d_ptr->tlsEllipticCurves_ = tlsEllipticCurves;
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QObject *parent)
    : QObject{parent}, d_ptr{new RTCIceServerPrivate()}
{
    init(urlStrings, QString(), QString(), RTCTlsCertPolicy::TlsCertPolicySecure, {}, {}, {});
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           QObject *parent)
    : QObject{parent}, d_ptr{new RTCIceServerPrivate()}
{
    init(urlStrings, username, credential, RTCTlsCertPolicy::TlsCertPolicySecure, {}, {}, {});
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QObject *parent)
    : QObject{parent}
{
    init(urlStrings, username, credential, tlsCertPolicy, QString(), {}, {});
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname, QObject *parent)
    : QObject{parent}
{
    init(urlStrings, username, credential, tlsCertPolicy, hostname, {}, {});
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                           QVector<QString> tlsAlpnProtocols, QObject *parent)
    : QObject{parent}
{
    init(urlStrings, username, credential, tlsCertPolicy, hostname, tlsAlpnProtocols, {});
}

RTCIceServer::RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                           RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                           QVector<QString> tlsAlpnProtocols, QVector<QString> tlsEllipticCurves,
                           QObject *parent)
    : QObject{parent}
{
    init(urlStrings, username, credential, tlsCertPolicy, hostname, tlsAlpnProtocols,
         tlsEllipticCurves);
}

QVector<QString> RTCIceServer::urlStrings() const
{
    Q_D(const RTCIceServer);
    return d->urlStrings_;
}

QString RTCIceServer::username() const
{
    Q_D(const RTCIceServer);
    return d->username_;
}

QString RTCIceServer::credential() const
{
    Q_D(const RTCIceServer);
    return d->credential_;
}

RTCTlsCertPolicy RTCIceServer::tlsCertPolicy() const
{
    Q_D(const RTCIceServer);
    return d->tlsCertPolicy_;
}

QString RTCIceServer::hostname() const
{
    Q_D(const RTCIceServer);
    return d->hostname_;
}

QVector<QString> RTCIceServer::tlsAlpnProtocols() const
{
    Q_D(const RTCIceServer);
    return d->tlsAlpnProtocols_;
}

QVector<QString> RTCIceServer::tlsEllipticCurves() const
{
    Q_D(const RTCIceServer);
    return d->tlsEllipticCurves_;
}
