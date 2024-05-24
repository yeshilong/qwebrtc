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

#ifndef RTCYUVPLANARBUFFER_H
#define RTCYUVPLANARBUFFER_H

#include <QObject>
#include <QByteArray>

#include "rtcvideoframebuffer.h"

/**
 * @brief Provides methods for handling YUV planar data.
 */
class IRTCYUVPlanarBuffer : public virtual IRTCVideoFrameBuffer
{
  public:
    IRTCYUVPlanarBuffer(QObject *parent = nullptr) : IRTCVideoFrameBuffer(parent)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, QObject *parent = nullptr)
        : IRTCVideoFrameBuffer(parent)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, int strideY, int strideU, int strideV,
                        QObject *parent = nullptr)
    {
    }
    IRTCYUVPlanarBuffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                        const uint8_t *dataV, QObject *parent = nullptr)
    {
    }

    virtual int chromaWidth() const = 0;
    virtual int chromaHeight() const = 0;
    virtual const uint8_t *dataY() const = 0;
    virtual const uint8_t *dataU() const = 0;
    virtual const uint8_t *dataV() const = 0;
    virtual int strideY() const = 0;
    virtual int strideU() const = 0;
    virtual int strideV() const = 0;
};

#endif // RTCYUVPLANARBUFFER_H
