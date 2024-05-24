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

#ifndef RTCNATIVEMUTABLEI420BUFFER_H
#define RTCNATIVEMUTABLEI420BUFFER_H

#include "rtcnativei420buffer.h"
#include "rtcmutableyuvplanarbuffer.h"

class RTCMutableI420BufferPrivate;
class RTCMutableI420Buffer : public RTCI420Buffer, public IRTCMutableYUVPlanarBuffer
{
  public:
    RTCMutableI420Buffer(int width, int height, QObject *parent = nullptr)
        : RTCI420Buffer(width, height, parent)
    {
    }
    RTCMutableI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                         QObject *parent = nullptr)
        : RTCI420Buffer(width, height, strideY, strideU, strideV, parent)
    {
    }

    RTCMutableI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                         const uint8_t *dataV, QObject *parent = nullptr)
        : RTCI420Buffer(width, height, dataY, dataU, dataV, parent)
    {
    }
    uint8_t *mutableDataY() const override;
    uint8_t *mutableDataU() const override;
    uint8_t *mutableDataV() const override;

  protected:
    RTCMutableI420BufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMutableI420Buffer)
};

#endif // RTCNATIVEMUTABLEI420BUFFER_H
