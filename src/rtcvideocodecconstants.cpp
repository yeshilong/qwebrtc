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

#include "rtcvideocodecconstants.h"

#include "media/base/media_constants.h"

QString RTCVideoCodecConstants::RTCVideoCodecVp8Name()
{
    return cricket::kVp8CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecVp9Name()
{
    return cricket::kVp9CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecAv1Name()
{
    return cricket::kAv1CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecH264Name()
{
    return cricket::kH264CodecName;
}
