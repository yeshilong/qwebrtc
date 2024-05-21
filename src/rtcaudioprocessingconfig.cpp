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

#include "rtcaudioprocessingconfig_p.h"

webrtc::AudioProcessing::Config RTCAudioProcessingConfigPrivate::nativeAudioProcessingConfig() const
{
    return nativeAudioProcessingConfig_;
}

RTCAudioProcessingConfigPrivate::RTCAudioProcessingConfigPrivate()
{
}

RTCAudioProcessingConfig::RTCAudioProcessingConfig(QObject *parent)
    : QObject{parent}, d_ptr{new RTCAudioProcessingConfigPrivate{}}
{
}

RTCAudioProcessingConfig::RTCAudioProcessingConfig(RTCAudioProcessingConfigPrivate &d,
                                                   QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

bool RTCAudioProcessingConfig::echoCancellerEnabled() const
{
    Q_D(const RTCAudioProcessingConfig);
    return d->nativeAudioProcessingConfig().echo_canceller.enabled;
}

void RTCAudioProcessingConfig::setEchoCancellerEnabled(bool echoCancellerEnabled)
{
    Q_D(RTCAudioProcessingConfig);
    d->nativeAudioProcessingConfig_.echo_canceller.enabled = echoCancellerEnabled;
}

bool RTCAudioProcessingConfig::echoCancellerMobileMode() const
{
    Q_D(const RTCAudioProcessingConfig);
    return d->nativeAudioProcessingConfig_.echo_canceller.mobile_mode;
}

void RTCAudioProcessingConfig::setEchoCancellerMobileMode(bool echoCancellerMobileMode)
{
    Q_D(RTCAudioProcessingConfig);
    d->nativeAudioProcessingConfig_.echo_canceller.mobile_mode = echoCancellerMobileMode;
}
