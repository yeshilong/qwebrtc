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

#ifndef RTCNATIVEI420BUFFER_H
#define RTCNATIVEI420BUFFER_H

#include "rtcyuvplanarbuffer.h"

#include <QString>

class RTCI420BufferPrivate;
/**
 * @brief Implements the RTCI420Buffer interface.
 */
class RTCI420Buffer : public virtual IRTCYUVPlanarBuffer
{
  public:
    RTCI420Buffer();

    /**
     * @brief Constructs an IRTCVideoFrameBuffer object.
     */
    RTCI420Buffer(QObject *parent = nullptr) : IRTCYUVPlanarBuffer(parent)
    {
    }

    explicit RTCI420Buffer(int width, int height, QObject *parent = nullptr);
    RTCI420Buffer(int width, int height, int strideY, int strideU, int strideV,
                  QObject *parent = nullptr);
    RTCI420Buffer(int width, int height, const uint8_t *dataY, const uint8_t *dataU,
                  const uint8_t *dataV, QObject *parent = nullptr);

    int width() const;
    int height() const;

    RTCI420Buffer *toI420();
    RTCI420Buffer *cropAndScaleWith(int offsetX, int offsetY, int cropWidth, int cropHeight,
                                    int scaleWidth, int scaleHeight);

    int chromaWidth() const;
    int chromaHeight() const;
    const uint8_t *dataY() const;
    const uint8_t *dataU() const;
    const uint8_t *dataV() const;
    int strideY() const;
    int strideU() const;
    int strideV() const;

  public:
    RTCI420Buffer(RTCI420BufferPrivate &d, QObject *parent = nullptr);

  private:
    RTCI420BufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCI420Buffer)
};

#endif // RTCNATIVEI420BUFFER_H
