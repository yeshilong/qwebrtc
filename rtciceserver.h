#ifndef RTCICESERVER_H
#define RTCICESERVER_H

#include <QObject>
#include <QString>
#include <QVector>

#include "rtctypes.h"

class RTCIceServerPrivate;

/**
 * @brief The RTCIceServer class represents an ICE server.
 */
class RTCIceServer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes an RTCIceServer with its associated URLs.
     */
    explicit RTCIceServer(QVector<QString> urlStrings, QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceServer with its associated URLs, optional username, and optional credential.
     */
    RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                 QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceServer with its associated URLs, optional username,
     * optional credential, and TLS cert policy.
     */
    RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                 RTCTlsCertPolicy tlsCertPolicy, QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceServer with its associated URLs, user name, credential, TLS cert policy, and hostname.
     */
    RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                 RTCTlsCertPolicy tlsCertPolicy, QString hostname, QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceServer with its associated URLs, user name, credential, TLS cert policy, hostname, and TLS ALPN protocols.
     */
    RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                 RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                 QVector<QString> tlsAlpnProtocols, QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceServer with its associated URLs, optional username,
     * optional credential, TLS cert policy, hostname, ALPN protocols and
     * elliptic curves.
     */
    RTCIceServer(QVector<QString> urlStrings, QString username, QString credential,
                 RTCTlsCertPolicy tlsCertPolicy, QString hostname,
                 QVector<QString> tlsAlpnProtocols, QVector<QString> tlsEllipticCurves,
                 QObject *parent = nullptr);

    /**
     * @brief Gets the URI(s) for this server represented as Strings.
     * @return The URI(s) for this server.
     */
    QVector<QString> urlStrings() const;

    /**
     * @brief Gets the username to use if this RTCIceServer object is a TURN server.
     * @return The username.
     */
    QString username() const;

    /**
     * @brief Gets the credential to use if this RTCIceServer object is a TURN server.
     * @return The credential.
     */
    QString credential() const;

    /**
     * @brief Gets the TLS certificate policy to use if this RTCIceServer object is a TURN server.
     * @return The TLS certificate policy.
     */
    RTCTlsCertPolicy tlsCertPolicy() const;

    /**
     * @brief Gets the hostname. If the URIs in `urls` only contain IP addresses, this field can be used
     * to indicate the hostname, which may be necessary for TLS (using the SNI extension). If `urls` itself contains the hostname, this isn't necessary.
     * @return The hostname.
     */
    QString hostname() const;

    /**
     * @brief Gets the list of protocols to be used in the TLS ALPN extension.
     * @return The list of protocols.
     */
    QVector<QString> tlsAlpnProtocols() const;

    /**
     * @brief Gets the list of elliptic curves to be used in the TLS elliptic curves extension.
     * Only curve names supported by OpenSSL should be used (eg. "P-256","X25519").
     * @return The list of elliptic curves.
     */
    QVector<QString> tlsEllipticCurves() const;

  private:
    Q_DECLARE_PRIVATE(RTCIceServer)
    RTCIceServerPrivate *d_ptr;
};

#endif // RTCICESERVER_H
