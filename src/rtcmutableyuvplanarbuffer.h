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

#ifndef RTCMUTABLEYUVPLANARBUFFER_H
#define RTCMUTABLEYUVPLANARBUFFER_H

#include "rtcyuvplanarbuffer.h"

class IRTCMutableYUVPlanarBuffer : public virtual IRTCYUVPlanarBuffer
{
  public:
    IRTCMutableYUVPlanarBuffer(QObject *parent = nullptr) : IRTCYUVPlanarBuffer(parent)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height) : IRTCYUVPlanarBuffer(width, height)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height, int strideY, int strideU, int strideV)
        : IRTCYUVPlanarBuffer(width, height, strideY, strideU, strideV)
    {
    }
    IRTCMutableYUVPlanarBuffer(int width, int height, uint8_t *dataY, uint8_t *dataU,
                               uint8_t *dataV)
        : IRTCYUVPlanarBuffer(width, height, dataY, dataU, dataV)
    {
    }

    virtual uint8_t *mutableDataY() const = 0;
    virtual uint8_t *mutableDataU() const = 0;
    virtual uint8_t *mutableDataV() const = 0;
};

#endif // RTCMUTABLEYUVPLANARBUFFER_H
