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

#ifndef QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_H
#define QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_H

#include <QObject>

namespace webrtc
{
class AudioCustomProcessingAdapter;
} // namespace webrtc

class RTCAudioCustomProcessingAdapterPrivate;
class RTCAudioCustomProcessingAdapter : public QObject
{
  public:
    explicit RTCAudioCustomProcessingAdapter(QObject *parent = nullptr);
    ~RTCAudioCustomProcessingAdapter() override;

  private:
    RTCAudioCustomProcessingAdapterPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCAudioCustomProcessingAdapter);

    friend class webrtc::AudioCustomProcessingAdapter;
    friend class RTCDefaultAudioProcessingModule;
};

#endif //QWEBRTC_RTCAUDIOCUSTOMPROCESSINGADAPTER_H
