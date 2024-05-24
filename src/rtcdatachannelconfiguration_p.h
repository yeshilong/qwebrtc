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

#ifndef RTCDATACHANNELCONFIGURATION_P_H
#define RTCDATACHANNELCONFIGURATION_P_H

#include "rtcdatachannelconfiguration.h"

#include <QString>

#include "api/data_channel_interface.h"

class RTCDataChannelConfigurationPrivate
{
  public:
    RTCDataChannelConfigurationPrivate();
    webrtc::DataChannelInit nativeDataChannelInit() const;

    webrtc::DataChannelInit nativeDataChannelInit_;
    int maxPacketLifeTime_;
    int channelId_;
};

#endif // RTCDATACHANNELCONFIGURATION_P_H
