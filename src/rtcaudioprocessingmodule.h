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

#ifndef RTCAUDIOPROCESSINGMODULE_H
#define RTCAUDIOPROCESSINGMODULE_H

#include <QObject>

#include "rtcaudioprocessingconfig.h"

/**
 * @brief Represents a module for audio processing.
 */
class IRTCAudioProcessingModule : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Applies the specified audio processing configuration.
     * @param config The audio processing configuration.
     */
    virtual void applyConfig(RTCAudioProcessingConfig &config) = 0;
};

#endif // RTCAUDIOPROCESSINGMODULE_H
