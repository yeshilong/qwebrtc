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

#ifndef RTCVIDEOFRAMEBUFFER_H
#define RTCVIDEOFRAMEBUFFER_H

#include <QObject>
#include <QByteArray>

class RTCI420Buffer;

/**
 * @brief Provides methods for handling video frame buffers.
 */
class IRTCVideoFrameBuffer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoFrameBuffer object.
     */
    explicit IRTCVideoFrameBuffer(QObject *parent = nullptr) : QObject(parent)
    {
    }
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual RTCI420Buffer *toI420() = 0;
    virtual IRTCVideoFrameBuffer *cropAndScaleWith(int offsetX, int offsetY, int cropWidth,
                                                   int cropHeight, int scaleWidth,
                                                   int scaleHeight) = 0;
};

#endif // RTCVIDEOFRAMEBUFFER_H
