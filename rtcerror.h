#ifndef RTCERROR_H
#define RTCERROR_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

/**
 * @brief The RTCConfiguration defines a set of parameters to configure how
 * the peer-to-peer communication established via RTCPeerConnection is
 * established or re-established.
 */
class RTCError : public QObject
{
public:
    explicit RTCError(QObject *parent = nullptr);

    /**
     * @brief Gets the error type;
     */
    RTCErrorType type() const;

    /**
     * @brief Gets the error message;
     */
    QString message() const;

    /**
     * @brief Gets true if the error is not an error.
     */
    bool ok() const;
};

#endif // RTCERROR_H
