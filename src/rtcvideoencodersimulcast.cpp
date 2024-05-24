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

#include "rtcvideoencodersimulcast.h"

#include "rtcwrappednativevideoencoder.h"
#include "rtcvideocodecinfo_p.h"

#include "native/objc_video_encoder_factory.h"

#include "media/engine/simulcast_encoder_adapter.h"

IRTCVideoEncoder *RTCVideoEncoderSimulcast::simulcastEncoderWithPrimary(
    IRTCVideoEncoderFactory *primary, IRTCVideoEncoderFactory *fallback,
    RTCVideoCodecInfo *videoCodecInfo)
{
    auto nativePrimary = webrtc::ObjCToNativeVideoEncoderFactory(primary);
    auto nativeFallback = webrtc::ObjCToNativeVideoEncoderFactory(fallback);
    auto nativeFormat = videoCodecInfo->d_ptr->nativeSdpVideoFormat();

    return new RTCWrappedNativeVideoEncoder(std::make_unique<webrtc::SimulcastEncoderAdapter>(
        nativePrimary.release(), nativeFallback.release(), std::move(nativeFormat)));
}
