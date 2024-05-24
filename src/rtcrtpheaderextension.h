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

#ifndef RTCRTPHEADEREXTENSION_H
#define RTCRTPHEADEREXTENSION_H

#include <QObject>
#include <QString>

class RTCRtpHeaderExtensionPrivate;
/**
 * @brief The RTCRtpHeaderExtension class.
 */
class RTCRtpHeaderExtension : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpHeaderExtension object.
     */
    explicit RTCRtpHeaderExtension(QObject *parent = nullptr);

    /**
     * @brief Gets the URI of the RTP header extension.
     * @return The URI of the RTP header extension.
     */
    QString uri() const;

    /**
     * @brief Gets the ID of the RTP header extension.
     * @return The ID of the RTP header extension.
     */
    int id() const;

    /**
     * @brief Gets whether the header extension is encrypted or not.
     * @return True if the header extension is encrypted, false otherwise.
     */
    bool encrypted() const;

  protected:
    RTCRtpHeaderExtension(RTCRtpHeaderExtensionPrivate *d, QObject *parent = nullptr);

    RTCRtpHeaderExtensionPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpHeaderExtension)

  private:
    friend class RTCRtpParametersPrivate;
    friend class RTCRtpParameters;
};

#endif // RTCRTPHEADEREXTENSION_H
