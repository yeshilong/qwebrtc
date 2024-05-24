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

#ifndef RTCVIDEOENCODERSETTINGS_P_H
#define RTCVIDEOENCODERSETTINGS_P_H

#include "rtcvideoencodersettings.h"

#include "modules/video_coding/include/video_codec_interface.h"

class RTCVideoEncoderSettingsPrivate
{
  public:
    RTCVideoEncoderSettingsPrivate();
    RTCVideoEncoderSettingsPrivate(const webrtc::VideoCodec *nativeVideoCodec);
    webrtc::VideoCodec nativeVideoCodec() const;

    QString name_;
    quint16 width_;
    quint16 height_;
    quint32 startBitrate_;
    quint32 maxBitrate_;
    quint32 minBitrate_;
    quint32 maxFramerate_;
    quint32 qpMax_;
    RTCVideoCodecMode mode_;
};

#endif // RTCVIDEOENCODERSETTINGS_P_H
