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

#ifndef RTCDATABUFFER_H
#define RTCDATABUFFER_H

#include <QObject>
#include <QByteArray>

class RTCDataBufferPrivate;
/**
 * @brief The RTCDataBuffer class represents a buffer of data to be sent through a data channel.
 */
class RTCDataBuffer : public QObject
{
    Q_OBJECT
  public:
    explicit RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent = nullptr);

    QByteArray data() const;
    bool isBinary() const;
    friend class RTCDataChannel;

  protected:
    RTCDataBufferPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCDataBuffer)
};

#endif // RTCDATABUFFER_H
