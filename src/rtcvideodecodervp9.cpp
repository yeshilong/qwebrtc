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

#include "rtcvideodecodervp9.h"
#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/vp9/include/vp9.h"

RTCVideoDecoderVP9::RTCVideoDecoderVP9(QObject *parent) : QObject{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderVP9::vp9Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::VP9Decoder::Create())};
}

bool RTCVideoDecoderVP9::isSupported()
{
#if defined(RTC_ENABLE_VP9)
    return true;
#else
    return false;
#endif
}
