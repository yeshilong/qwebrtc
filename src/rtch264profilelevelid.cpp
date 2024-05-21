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

#include "rtch264profilelevelid.h"

#include "api/video_codecs/h264_profile_level_id.h"
#include "media/base/media_constants.h"

QString RTCH264ProfileLevelId::RTCLevel31ConstrainedHigh()
{
    return "640c1f";
}

QString RTCH264ProfileLevelId::RTCLevel31ConstrainedBaseline()
{
    return "42e01f";
}

QString RTCH264ProfileLevelId::RTCMaxSupportedH264ProfileLevelConstrainedHigh()
{
    return RTCLevel31ConstrainedHigh();
}

QString RTCH264ProfileLevelId::RTCMaxSupportedH264ProfileLevelConstrainedBaseline()
{
    return RTCLevel31ConstrainedBaseline();
}