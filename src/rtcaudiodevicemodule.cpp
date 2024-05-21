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

#include "rtcaudiodevicemodule_p.h"

RTCAudioDeviceModulePrivate::RTCAudioDeviceModulePrivate(
    rtc::scoped_refptr<webrtc::AudioDeviceModule> audioDeviceModule, rtc::Thread *workerThread)
{
    _native = audioDeviceModule;
    _workerThread = workerThread;

    _sink = new AudioDeviceSink();

    _workerThread->BlockingCall([this] { _native->SetAudioDeviceSink(_sink); });
}

QVector<RTCIODevice *> RTCAudioDeviceModulePrivate::_outputDevices() const
{
    char guid[webrtc::kAdmMaxGuidSize + 1] = {0};
    char name[webrtc::kAdmMaxDeviceNameSize + 1] = {0};

    QVector<RTCIODevice *> result;

    int16_t count = _native->PlayoutDevices();

    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            _native->PlayoutDeviceName(i, name, guid);
            QString strGUID = QString::fromUtf8(guid);
            QString strName = QString::fromUtf8(name);
            RTCIODevice *device =
                new RTCIODevice(RTCIODeviceType::RTCIODeviceTypeOutput, strGUID, strName);
            result.append(device);
        }
    }

    return result;
}

QVector<RTCIODevice *> RTCAudioDeviceModulePrivate::_inputDevices() const
{
    char guid[webrtc::kAdmMaxGuidSize + 1] = {0};
    char name[webrtc::kAdmMaxDeviceNameSize + 1] = {0};

    QVector<RTCIODevice *> result;

    int16_t count = _native->RecordingDevices();

    if (count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            _native->RecordingDeviceName(i, name, guid);
            QString strGUID = QString::fromUtf8(guid);
            QString strName = QString::fromUtf8(name);
            RTCIODevice *device =
                new RTCIODevice(RTCIODeviceType::RTCIODeviceTypeInput, strGUID, strName);
            result.append(device);
        }
    }

    return result;
}

RTCAudioDeviceModule::RTCAudioDeviceModule(QObject *parent) : QObject{parent}
{
}

RTCAudioDeviceModule::RTCAudioDeviceModule(RTCAudioDeviceModulePrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
}

QVector<RTCIODevice *> RTCAudioDeviceModule::outputDevices() const
{
    Q_D(const RTCAudioDeviceModule);
    return d->_workerThread->BlockingCall([d] { return d->_outputDevices(); });
}

QVector<RTCIODevice *> RTCAudioDeviceModule::inputDevices() const
{
    Q_D(const RTCAudioDeviceModule);
    return d->_workerThread->BlockingCall([d] { return d->_inputDevices(); });
}

bool RTCAudioDeviceModule::isPlaying() const
{
    Q_D(const RTCAudioDeviceModule);
    return d->_workerThread->BlockingCall([d] { return d->_native->Playing(); });
}

bool RTCAudioDeviceModule::isRecording() const
{
    Q_D(const RTCAudioDeviceModule);
    return d->_workerThread->BlockingCall([d] { return d->_native->Recording(); });
}

RTCIODevice *RTCAudioDeviceModule::outputDevice() const
{
    Q_D(const RTCAudioDeviceModule);
    return d->_workerThread->BlockingCall([d]() {
        QVector<RTCIODevice *> devices = d->_outputDevices();
        int16_t devicesCount = static_cast<int16_t>(devices.size());
        int16_t index = d->_native->GetPlayoutDevice();

        if (devicesCount == 0 || index <= -1 || index > (devicesCount - 1))
        {
            return static_cast<RTCIODevice *>(nullptr);
        }

        return static_cast<RTCIODevice *>(devices[index]);
    });
}
