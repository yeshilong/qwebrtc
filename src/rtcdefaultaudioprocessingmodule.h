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

#ifndef RTCDEFAULTAUDIOPROCESSINGMODULE_H
#define RTCDEFAULTAUDIOPROCESSINGMODULE_H

#include <QObject>

#include "rtcaudiocustomprocessingdelegate.h"
#include "rtcaudioprocessingmodule.h"
#include "rtcdefaultaudioprocessingmodule.h"

class RTCAudioProcessingConfig;
class RTCDefaultAudioProcessingModulePrivate;
/**
 * @brief Represents the default audio processing module containing various properties and methods.
 */
class RTCDefaultAudioProcessingModule : public IRTCAudioProcessingModule
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCDefaultAudioProcessingModule class.
     * @param parent The parent object.
     */
    RTCDefaultAudioProcessingModule(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCDefaultAudioProcessingModule class.
     * @param config The audio processing configuration.
     * @param capturePostProcessingDelegate The capture post-processing delegate.
     * @param renderPreProcessingDelegate The render pre-processing delegate.
     */
    RTCDefaultAudioProcessingModule(RTCAudioProcessingConfig *config,
                                    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate,
                                    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate);

    /**
     * @brief Gets and sets the capture post-processing delegate.
     * @return The capture post-processing delegate.
     */
    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate() const;
    void setCapturePostProcessingDelegate(
        RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate);

    /**
     * @brief Gets and sets the render pre-processing delegate.
     * @return The render pre-processing delegate.
     */
    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate() const;
    void setRenderPreProcessingDelegate(
        RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate);

    /**
     * @brief Applies the specified audio processing configuration.
     * @param config The audio processing configuration.
     */
    void applyConfig(RTCAudioProcessingConfig &config) override;

  private:
    RTCDefaultAudioProcessingModulePrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDefaultAudioProcessingModule)

    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate_;
    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate_;

    friend class RTCPeerConnectionFactory;
};

#endif // RTCDEFAULTAUDIOPROCESSINGMODULE_H
