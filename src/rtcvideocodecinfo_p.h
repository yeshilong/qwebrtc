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

#ifndef RTCVIDEOCODECINFO_P_H
#define RTCVIDEOCODECINFO_P_H

#include "rtcvideocodecinfo.h"

#include "absl/container/inlined_vector.h"
#include "api/video_codecs/sdp_video_format.h"
#include "modules/video_coding/svc/scalability_mode_util.h"
#include "modules/video_coding/svc/create_scalability_structure.h"

class RTCVideoCodecInfoPrivate
{
  public:
    RTCVideoCodecInfoPrivate(const webrtc::SdpVideoFormat &format);

    webrtc::SdpVideoFormat nativeSdpVideoFormat() const;

    QString name_;
    QMap<QString, QString> parameters_;
    QVector<QString> scalabilityModes_;
};

#endif // RTCVIDEOCODECINFO_P_H
