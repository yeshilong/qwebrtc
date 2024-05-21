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

#ifndef RTCAUDIODEVICEMODULE_P_H
#define RTCAUDIODEVICEMODULE_P_H

#include "rtcaudiodevicemodule.h"
#include "rtclogging.h"

#include "rtc_base/thread.h"
#include "modules/audio_device/include/audio_device.h"

class AudioDeviceSink : public webrtc::AudioDeviceSink
{
  public:
    AudioDeviceSink()
    {
    }

    void OnDevicesUpdated() override
    {

        RTCLogInfo("AudioDeviceSink OnDevicesUpdated");

        if (callback_handler_)
        {
            callback_handler_();
        }
    }

    // private:
    RTCOnAudioDevicesDidUpdate callback_handler_;
};

class RTCAudioDeviceModulePrivate
{
  public:
    RTCAudioDeviceModulePrivate(rtc::scoped_refptr<webrtc::AudioDeviceModule> audioDeviceModule,
                                rtc::Thread *workerThread);

    QVector<RTCIODevice *> _inputDevices() const;
    QVector<RTCIODevice *> _outputDevices() const;

    rtc::Thread *_workerThread;
    rtc::scoped_refptr<webrtc::AudioDeviceModule> _native;
    AudioDeviceSink *_sink;
};

#endif //RTCAUDIODEVICEMODULE_P_H
