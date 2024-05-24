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

#ifndef RTCRTCPPARAMETERS_H
#define RTCRTCPPARAMETERS_H

#include <QObject>
#include <QString>

class RTCRtcpParametersPrivate;
/**
 * @brief The RTCRtcpParameters class.
 */
class RTCRtcpParameters : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtcpParameters object.
     */
    explicit RTCRtcpParameters(QObject *parent = nullptr);

    /**
     * @brief Gets the Canonical Name used by RTCP.
     * @return The Canonical Name used by RTCP.
     */
    QString cname() const;

    /**
     * @brief Sets the Canonical Name used by RTCP.
     * @param cname The Canonical Name to be used by RTCP.
     */
    void setCname(const QString &cname);

    /**
     * @brief Checks whether reduced size RTCP is configured or compound RTCP.
     * @return True if reduced size RTCP is configured, false if compound RTCP is configured.
     */
    bool isReducedSize() const;

    /**
     * @brief Sets whether to configure reduced size RTCP or compound RTCP.
     * @param isReducedSize True to configure reduced size RTCP, false to configure compound RTCP.
     */
    void setIsReducedSize(bool isReducedSize);

  protected:
    RTCRtcpParameters(RTCRtcpParametersPrivate *d, QObject *parent = nullptr);

  private:
    friend class RTCRtpParametersPrivate;
    friend class RTCRtpParameters;

    RTCRtcpParametersPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtcpParameters)
};

#endif // RTCRTCPPARAMETERS_H
