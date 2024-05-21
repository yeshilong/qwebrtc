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

#ifndef RTCAUDIOPROCESSINGCONFIG_H
#define RTCAUDIOPROCESSINGCONFIG_H

#include <QObject>

class RTCAudioProcessingConfigPrivate;
/**
 * @brief Represents configuration parameters for audio processing.
 */
class RTCAudioProcessingConfig : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an instance of the RTCAudioProcessingConfig class.
     * @param parent The parent object.
     */
    explicit RTCAudioProcessingConfig(QObject *parent = nullptr);

    /**
     * @brief Constructs an instance of the RTCAudioProcessingConfig class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCAudioProcessingConfig(RTCAudioProcessingConfigPrivate &d,
                                      QObject *parent = nullptr);

    /**
     * @brief Gets and sets the state of the echo canceler.
     * @return True if the echo canceler is enabled, false otherwise.
     */
    bool echoCancellerEnabled() const;
    void setEchoCancellerEnabled(bool echoCancellerEnabled);

    /**
     * @brief Gets and sets the state of the echo canceler mobile mode.
     * @return True if the echo canceler mobile mode is enabled, false otherwise.
     */
    bool echoCancellerMobileMode() const;
    void setEchoCancellerMobileMode(bool echoCancellerMobileMode);

  private:
    RTCAudioProcessingConfigPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCAudioProcessingConfig)

    friend class RTCDefaultAudioProcessingModule;
};

#endif // RTCAUDIOPROCESSINGCONFIG_H
