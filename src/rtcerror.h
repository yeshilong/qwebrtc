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

#ifndef RTCERROR_H
#define RTCERROR_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCErrorPrivate;
/**
 * @brief The RTCConfiguration defines a set of parameters to configure how
 * the peer-to-peer communication established via RTCPeerConnection is
 * established or re-established.
 */
class RTCError : public QObject
{
  public:
    explicit RTCError(QObject *parent = nullptr);
    RTCError(RTCErrorPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the error type;
     */
    RTCErrorType type() const;

    /**
     * @brief Gets the error detail;
     */
    RTCErrorDetailType detail() const;

    /**
     * @brief Gets the error message;
     */
    QString message() const;

    /**
     * @brief Gets true if the error is not an error.
     */
    bool ok() const;

  private:
    RTCErrorPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCError)
};

#endif // RTCERROR_H
