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

#ifndef QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_P_H
#define QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_P_H

#include "rtcaudiocustomprocessingadapter.h"
#include "rtcaudiocustomprocessingdelegate.h"
#include "rtcaudiobuffer_p.h"

#include "rtc_base/logging.h"
#include "modules/audio_processing/include/audio_processing.h"

class RTCAudioCustomProcessingAdapterPrivate
{
  public:
    explicit RTCAudioCustomProcessingAdapterPrivate(
        std::shared_ptr<RTCAudioCustomProcessingDelegate> audioCustomProcessingDelegate);

    void setAudioCustomProcessingDelegate(
        std::shared_ptr<RTCAudioCustomProcessingDelegate> delegate);
    std::shared_ptr<RTCAudioCustomProcessingDelegate> audioCustomProcessingDelegate() const;
    std::shared_ptr<RTCAudioCustomProcessingDelegate> rawAudioCustomProcessingDelegate() const;
    std::unique_ptr<webrtc::CustomProcessing> nativeAudioCustomProcessingModule() const;

    std::weak_ptr<RTCAudioCustomProcessingDelegate> audioCustomProcessingDelegate_;
    std::weak_ptr<RTCAudioCustomProcessingDelegate> rawAudioCustomProcessingDelegate_;
    std::unique_ptr<webrtc::CustomProcessing> nativeAudioCustomProcessingModule_;

    webrtc::AudioCustomProcessingAdapter *adapter_;

    std::mutex lock_;
};

namespace webrtc
{
class AudioCustomProcessingAdapter : public webrtc::CustomProcessing
{
  public:
    bool is_initialized_;
    int sample_rate_hz_;
    int num_channels_;

    AudioCustomProcessingAdapter(std::shared_ptr<RTCAudioCustomProcessingAdapterPrivate> adapter,
                                 std::mutex *lock)
    {
        RTC_LOG(LS_INFO) << "RTCAudioCustomProcessingAdapter.AudioCustomProcessingAdapter init";

        adapter_ = adapter;
        lock_ = lock;
        is_initialized_ = false;
        sample_rate_hz_ = 0;
        num_channels_ = 0;
    }

    ~AudioCustomProcessingAdapter() override
    {
        RTC_LOG(LS_INFO) << "RTCAudioCustomProcessingAdapter.AudioCustomProcessingAdapter dealloc";

        lock_->lock();
        auto delegate = adapter_.lock()->rawAudioCustomProcessingDelegate();
        delegate->audioProcessingRelease();
        lock_->unlock();
    }

    void Initialize(int sample_rate_hz, int num_channels) override
    {
        lock_->lock();
        auto delegate = adapter_.lock()->rawAudioCustomProcessingDelegate();
        delegate->audioProcessingInitialize(sample_rate_hz, num_channels);
        is_initialized_ = true;
        sample_rate_hz_ = sample_rate_hz;
        num_channels_ = num_channels;
        lock_->unlock();
    }

    void Process(AudioBuffer *audio_buffer) override
    {
        bool is_locked = lock_->try_lock();
        if (!is_locked)
        {
            RTC_LOG(LS_INFO)
                << "RTCAudioCustomProcessingAdapter.AudioCustomProcessingAdapter Process "
                   "already locked, skipping...";

            return;
        }
        auto delegate = adapter_.lock()->rawAudioCustomProcessingDelegate();
        if (delegate != nullptr)
        {
            RTCAudioBuffer *audioBuffer =
                new RTCAudioBuffer(new RTCAudioBufferPrivate(audio_buffer));
            delegate->audioProcessingProcess(audioBuffer);
        }
        lock_->unlock();
    }

    std::string ToString() const override
    {
        return "AudioCustomProcessingAdapter";
    }

  private:
    std::weak_ptr<RTCAudioCustomProcessingAdapterPrivate> adapter_;
    std::mutex *lock_;
};
} // namespace webrtc

#endif //QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_P_H
