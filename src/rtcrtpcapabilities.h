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

#ifndef RTCRTPCAPABILITIES_H
#define RTCRTPCAPABILITIES_H

#include <QObject>
#include <QVector>

class RTCRtpCodecCapability;
class RTCRtpCapabilitiesPrivate;
/**
 * @brief The RTCRtpCapabilities class.
 */
class RTCRtpCapabilities : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpCapabilities object.
     */
    explicit RTCRtpCapabilities(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCRtpCapabilities object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCRtpCapabilities(RTCRtpCapabilitiesPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the codecs supported.
     * @return The codecs supported.
     */
    QVector<RTCRtpCodecCapability *> codecs() const;

    // Not implemented.
    // QVector<RtpHeaderExtensionCapability*> headerExtensions;

    // Not implemented.
    // QVector<FecMechanism*> fec;

  private:
    RTCRtpCapabilitiesPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpCapabilities)
};

#endif // RTCRTPCAPABILITIES_H
