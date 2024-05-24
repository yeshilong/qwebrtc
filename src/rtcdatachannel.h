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

#ifndef RTCDATACHANNEL_H
#define RTCDATACHANNEL_H

#include <QObject>
#include <QString>
#include <QByteArray>

#include "rtctypes.h"
#include "rtcdatabuffer.h"

class RTCDataChannelPrivate;
/**
 * @brief The RTCDataChannel class represents a data channel with various properties and methods.
 */
class RTCDataChannel : public QObject
{
    Q_OBJECT
  public:
    explicit RTCDataChannel(RTCDataChannelPrivate &d, QObject *parent = nullptr);
    ~RTCDataChannel();

    QString label() const;
    bool isReliable() const;
    bool isOrdered() const;
    unsigned int maxRetransmitTime() const;
    unsigned short maxPacketLifeTime() const;
    unsigned short maxRetransmits() const;
    QString protocol() const;
    bool isNegotiated() const;
    int streamId() const;
    int channelId() const;
    RTCDataChannelState readyState() const;
    unsigned long long bufferedAmount() const;

    void close();
    bool sendData(const RTCDataBuffer *data);

  Q_SIGNALS:
    void dataChannelDidChangeState();
    void dataChannelDidReceiveMessageWithBuffer(const QByteArray &buffer);
    void dataChannelDidChangeBufferedAmount(unsigned long long amount);

  private:
    RTCDataChannelPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDataChannel)
};

#endif // RTCDATACHANNEL_H
