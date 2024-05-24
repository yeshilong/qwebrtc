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

#ifndef RTCCODECSPECIFICINFOH264_H
#define RTCCODECSPECIFICINFOH264_H

#include <QObject>

#include "rtctypes.h"
#include "rtccodecspecificinfo.h"

namespace webrtc
{

namespace
{
class ObjCVideoEncoder;
class ObjCVideoEncoderSelector;
} // namespace

class ObjCVideoDecoderFactory;
class ObjCVideoEncoderFactory;

} // namespace webrtc

class RTCCodecSpecificInfoH264Private;
/**
 * @brief The RTCCodecSpecificInfoH264 class.
 */
class RTCCodecSpecificInfoH264 : public IRTCCodecSpecificInfo
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCCodecSpecificInfoH264 object.
     */
    explicit RTCCodecSpecificInfoH264(QObject *parent = nullptr);

    /**
     * @brief Gets the packetization mode for H264 codec.
     * @return The packetization mode for H264 codec.
     */
    RTCH264PacketizationMode packetizationMode() const;

    /**
     * @brief Sets the packetization mode for H264 codec.
     * @param packetizationMode The packetization mode for H264 codec.
     */
    void setPacketizationMode(RTCH264PacketizationMode packetizationMode);

  private:
    friend class webrtc::ObjCVideoEncoder;

    RTCCodecSpecificInfoH264Private *const d_ptr;
    Q_DECLARE_PRIVATE(RTCCodecSpecificInfoH264)
};

#endif // RTCCODECSPECIFICINFOH264_H
