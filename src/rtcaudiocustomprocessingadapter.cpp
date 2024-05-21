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

#include "rtcaudiocustomprocessingadapter_p.h"

RTCAudioCustomProcessingAdapterPrivate::RTCAudioCustomProcessingAdapterPrivate(
    std::shared_ptr<RTCAudioCustomProcessingDelegate> audioCustomProcessingDelegate)
    : audioCustomProcessingDelegate_{audioCustomProcessingDelegate}
{
}

std::shared_ptr<RTCAudioCustomProcessingDelegate> RTCAudioCustomProcessingAdapterPrivate::
    audioCustomProcessingDelegate() const
{
    return audioCustomProcessingDelegate_.lock();
}

void RTCAudioCustomProcessingAdapterPrivate::setAudioCustomProcessingDelegate(
    std::shared_ptr<RTCAudioCustomProcessingDelegate> delegate)
{
    lock_.lock();
    if (rawAudioCustomProcessingDelegate_.lock() != nullptr && adapter_->is_initialized_)
    {
        rawAudioCustomProcessingDelegate_.lock()->audioProcessingRelease();
    }
    rawAudioCustomProcessingDelegate_ = delegate;
    if (adapter_->is_initialized_)
    {
        rawAudioCustomProcessingDelegate_.lock()->audioProcessingInitialize(
            adapter_->sample_rate_hz_, adapter_->num_channels_);
    }
}

std::shared_ptr<RTCAudioCustomProcessingDelegate> RTCAudioCustomProcessingAdapterPrivate::
    rawAudioCustomProcessingDelegate() const
{
    return rawAudioCustomProcessingDelegate_.lock();
}

std::unique_ptr<webrtc::CustomProcessing> RTCAudioCustomProcessingAdapterPrivate::
    nativeAudioCustomProcessingModule() const
{
    return std::unique_ptr<webrtc::CustomProcessing>(adapter_);
}

RTCAudioCustomProcessingAdapter::RTCAudioCustomProcessingAdapter(QObject *parent)
    : QObject{parent}, d_ptr{new RTCAudioCustomProcessingAdapterPrivate{nullptr}}
{
    RTC_LOG(LS_INFO) << "RTCAudioCustomProcessingAdapter init";
}

RTCAudioCustomProcessingAdapter::~RTCAudioCustomProcessingAdapter()
{
    RTC_LOG(LS_INFO) << "RTCAudioCustomProcessingAdapter dealloc";
}