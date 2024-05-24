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

#ifndef RTCDATACHANNELCONFIGURATION_H
#define RTCDATACHANNELCONFIGURATION_H

#include <QObject>
#include <QString>

class RTCDataChannelConfigurationPrivate;
/**
 * @brief The RTCDataChannelConfiguration class represents a configuration for a data channel with various properties.
 */
class RTCDataChannelConfiguration : public QObject
{
    Q_OBJECT

  public:
    explicit RTCDataChannelConfiguration(QObject *parent = nullptr);

    bool isOrdered() const;
    void setIsOrdered(bool ordered);

    int maxRetransmitTimeMs() const;
    void setMaxRetransmitTimeMs(int time);

    int maxPacketLifeTime() const;
    void setMaxPacketLifeTime(int time);

    int maxRetransmits() const;
    void setMaxRetransmits(int retransmits);

    bool isNegotiated() const;
    void setIsNegotiated(bool negotiated);

    int streamId() const;
    void setStreamId(int id);

    int channelId() const;
    void setChannelId(int id);

    QString protocol() const;
    void setProtocol(const QString &protocol);

  private:
    RTCDataChannelConfigurationPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDataChannelConfiguration)

    friend class RTCPeerConnection;
};

#endif // RTCDATACHANNELCONFIGURATION_H
