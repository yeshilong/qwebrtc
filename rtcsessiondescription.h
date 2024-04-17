#ifndef RTCSESSIONDESCRIPTION_H
#define RTCSESSIONDESCRIPTION_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

/**
 * @brief The RTCSessionDescription class.
 */
class RTCSessionDescription : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCSessionDescription object.
     */
    explicit RTCSessionDescription(QObject *parent = nullptr);

    /**
     * @brief Initialize a session description with a type and SDP string.
     * @param type The type of session description.
     * @param sdp The SDP string representation of this session description.
     */
    RTCSessionDescription(RTCSdpType type, QString sdp, QObject *parent = nullptr);

    /**
     * @brief Gets the type of session description.
     * @return The type of session description.
     */
    RTCSdpType type() const;

    /**
     * @brief Gets the SDP string representation of this session description.
     * @return The SDP string representation of this session description.
     */
    QString sdp() const;

    /**
     * @brief Get the string representation of a session description type.
     * @param type The type of session description.
     * @return The string representation of a session description type.
     */
    static QString stringForType(RTCSdpType type);

    /**
     * @brief Get the session description type for a string representation.
     * @param string The string representation of a session description type.
     * @return The session description type for a string representation.
     */
    static RTCSdpType typeForString(QString string);
};

#endif // RTCSESSIONDESCRIPTION_H
