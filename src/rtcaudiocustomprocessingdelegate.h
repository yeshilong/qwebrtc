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

#ifndef RTCAUDIOCUSTOMPROCESSINGDELEGATE_H
#define RTCAUDIOCUSTOMPROCESSINGDELEGATE_H

#include <QObject>

#include "rtcaudiobuffer.h"

/**
 * @brief Represents a delegate for custom audio processing.
 */
class RTCAudioCustomProcessingDelegate : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief (Re-)initialize the audio processor. This method can be invoked multiple times.
     * @param sampleRateHz The sample rate in Hz.
     * @param channels The number of channels.
     */
    virtual void audioProcessingInitialize(unsigned int sampleRateHz, unsigned int channels) = 0;

    /**
     * @brief Process (read or write) the audio buffer. RTCAudioBuffer is a simple wrapper for webrtc::AudioBuffer and the valid scope is only inside this method. Do not retain it.
     * @param audioBuffer The audio buffer.
     */
    virtual void audioProcessingProcess(RTCAudioBuffer *audioBuffer) = 0;

    /**
     * @brief Set runtime setting. This method can be invoked multiple times.
     * @param setting The runtime setting.
     */
    // TODO: virtual void setRuntimeSetting(AudioProcessing::RuntimeSetting setting) = 0;

    /**
     * @brief Suggests releasing resources allocated by the audio processor.
     */
    virtual void audioProcessingRelease() = 0;
};

#endif // RTCAUDIOCUSTOMPROCESSINGDELEGATE_H
