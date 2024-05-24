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

#ifndef RTCSESSIONDESCRIPTION_H
#define RTCSESSIONDESCRIPTION_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCSessionDescriptionPrivate;
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
    RTCSessionDescription(QObject *parent = nullptr) = delete;

    /**
     * @brief Constructs an RTCSessionDescription object.
     * @param d The private implementation.
     */
    explicit RTCSessionDescription(RTCSessionDescriptionPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Initialize a session description with a type and SDP string.
     * @param type The type of session description.
     * @param sdp The SDP string representation of this session description.
     */
    explicit RTCSessionDescription(RTCSdpType type, QString sdp, QObject *parent = nullptr);

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

  private:
    RTCSessionDescriptionPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCSessionDescription)

    friend class RTCPeerConnection;
};

#endif // RTCSESSIONDESCRIPTION_H
