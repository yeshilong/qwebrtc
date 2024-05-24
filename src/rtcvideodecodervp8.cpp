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

#include "rtcvideodecodervp8.h"
#include "rtcwrappednativevideodecoder.h"

#include "modules/video_coding/codecs/vp8/include/vp8.h"

RTCVideoDecoderVP8::RTCVideoDecoderVP8(QObject *parent) : QObject{parent}
{
}

IRTCVideoDecoder *RTCVideoDecoderVP8::vp8Decoder()
{
    return new RTCWrappedNativeVideoDecoder{
        std::unique_ptr<webrtc::VideoDecoder>(webrtc::VP8Decoder::Create())};
}
