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

#ifndef RTCICECANDIDATEERROREVENT_H
#define RTCICECANDIDATEERROREVENT_H

#include <QObject>
#include <QString>

/**
 * @brief Represents an error event that occurs during ICE candidate gathering.
 */
class RTCIceCandidateErrorEvent : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes an RTCIceCandidateErrorEvent.
     */
    explicit RTCIceCandidateErrorEvent(QObject *parent = nullptr);

    /**
     * @brief Initializes an RTCIceCandidateErrorEvent with the specified address, port, URL, error code, and error text.
     * @param address The local IP address used to communicate with the STUN or TURN server.
     * @param port The port used to communicate with the STUN or TURN server.
     * @param url The STUN or TURN URL that identifies the STUN or TURN server for which the failure occurred.
     * @param errorCode The numeric STUN error code returned by the STUN or TURN server.
     * @param errorText The STUN reason text returned by the STUN or TURN server.
     */
    RTCIceCandidateErrorEvent(const QString &address, int port, const QString &url, int errorCode,
                              const QString &errorText, QObject *parent = nullptr);

    /**
     * @brief Gets the local IP address used to communicate with the STUN or TURN server.
     * @return The local IP address.
     */
    QString address() const;

    /**
     * @brief Gets the port used to communicate with the STUN or TURN server.
     * @return The port.
     */
    int port() const;

    /**
     * @brief Gets the STUN or TURN URL that identifies the STUN or TURN server for which the failure occurred.
     * @return The STUN or TURN URL.
     */
    QString url() const;

    /**
     * @brief Gets the numeric STUN error code returned by the STUN or TURN server.
     * @return The numeric STUN error code.
     */
    int errorCode() const;

    /**
     * @brief Gets the STUN reason text returned by the STUN or TURN server.
     * @return The STUN reason text.
     */
    QString errorText() const;

  private:
    QString address_;
    int port_;
    QString url_;
    int errorCode_;
    QString errorText_;
};

#endif // RTCICECANDIDATEERROREVENT_H
