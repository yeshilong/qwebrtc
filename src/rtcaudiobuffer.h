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

#ifndef RTCAUDIOBUFFER_H
#define RTCAUDIOBUFFER_H

#include <QObject>
#include <QVector>

class RTCAudioBufferPrivate;
/**
 * @brief Represents an audio buffer with multiple properties.
 */
class RTCAudioBuffer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCAudioBuffer class.
     */
    explicit RTCAudioBuffer(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCAudioBuffer class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCAudioBuffer(RTCAudioBufferPrivate *d, QObject *parent = nullptr);

    /**
     * @brief Returns the number of channels.
     * @return The number of channels.
     */
    uint32_t channels() const;

    /**
     * @brief Returns the number of frames.
     * @return The number of frames.
     */
    uint32_t frames() const;

    /**
     * @brief Returns the number of frames per band.
     * @return The number of frames per band.
     */
    uint32_t framesPerBand() const;

    /**
     * @brief Returns the number of bands.
     * @return The number of bands.
     */
    uint32_t bands() const;

  private:
    RTCAudioBufferPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCAudioBuffer)
};

#endif // RTCAUDIOBUFFER_H
