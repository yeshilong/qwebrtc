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

#ifndef RTCCODECSPECIFICINFOH264_P_H
#define RTCCODECSPECIFICINFOH264_P_H

#include "rtccodecspecificinfoh264.h"

#include "modules/video_coding/include/video_codec_interface.h"

#include "rtctypes.h"

class RTCCodecSpecificInfoH264Private
{
  public:
    RTCCodecSpecificInfoH264Private();

    webrtc::CodecSpecificInfo nativeCodecSpecificInfo() const;

    RTCH264PacketizationMode packetizationMode() const;
    void setPacketizationMode(RTCH264PacketizationMode packetizationMode);

  private:
    RTCH264PacketizationMode packetizationMode_;
};

#endif // RTCCODECSPECIFICINFOH264_P_H
