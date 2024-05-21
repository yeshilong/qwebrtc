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

#include "rtcdefaultaudioprocessingmodule_p.h"
#include "rtcaudiocustomprocessingadapter_p.h"
#include "rtcaudioprocessingconfig_p.h"

RTCDefaultAudioProcessingModulePrivate::RTCDefaultAudioProcessingModulePrivate()
{
}

rtc::scoped_refptr<webrtc::AudioProcessing> RTCDefaultAudioProcessingModulePrivate::
    nativeAudioProcessingModule() const
{
    return nativeAudioProcessingModule_;
}

RTCDefaultAudioProcessingModule::RTCDefaultAudioProcessingModule(QObject *parent)
{
}

RTCDefaultAudioProcessingModule::RTCDefaultAudioProcessingModule(
    RTCAudioProcessingConfig *config,
    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate,
    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate)
{
    d_ptr = new RTCDefaultAudioProcessingModulePrivate();

    webrtc::AudioProcessingBuilder builder = webrtc::AudioProcessingBuilder();

    if (config != nullptr)
    {
        builder.SetConfig(config->d_ptr->nativeAudioProcessingConfig());
    }

    d_ptr->capturePostProcessingAdapter_ =
        new RTCAudioCustomProcessingAdapter(capturePostProcessingDelegate);
    builder.SetCapturePostProcessing(
        d_ptr->capturePostProcessingAdapter_->d_ptr->nativeAudioCustomProcessingModule());

    d_ptr->renderPreProcessingAdapter_ =
        new RTCAudioCustomProcessingAdapter(renderPreProcessingDelegate);
    builder.SetRenderPreProcessing(
        d_ptr->renderPreProcessingAdapter_->d_ptr->nativeAudioCustomProcessingModule());

    d_ptr->nativeAudioProcessingModule() = builder.Create();
}

RTCAudioCustomProcessingDelegate *RTCDefaultAudioProcessingModule::capturePostProcessingDelegate()
    const
{
    return d_ptr->capturePostProcessingAdapter_->d_ptr->audioCustomProcessingDelegate().get();
}

void RTCDefaultAudioProcessingModule::setCapturePostProcessingDelegate(
    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate)
{
    d_ptr->capturePostProcessingAdapter_->d_ptr->setAudioCustomProcessingDelegate(
        std::shared_ptr<RTCAudioCustomProcessingDelegate>(capturePostProcessingDelegate));
}

RTCAudioCustomProcessingDelegate *RTCDefaultAudioProcessingModule::renderPreProcessingDelegate()
    const
{
    return d_ptr->renderPreProcessingAdapter_->d_ptr->audioCustomProcessingDelegate().get();
}

void RTCDefaultAudioProcessingModule::setRenderPreProcessingDelegate(
    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate)
{
    d_ptr->renderPreProcessingAdapter_->d_ptr->setAudioCustomProcessingDelegate(
        std::shared_ptr<RTCAudioCustomProcessingDelegate>(renderPreProcessingDelegate));
}

void RTCDefaultAudioProcessingModule::applyConfig(RTCAudioProcessingConfig &config)
{
    d_ptr->nativeAudioProcessingModule()->ApplyConfig(config.d_ptr->nativeAudioProcessingConfig());
}
