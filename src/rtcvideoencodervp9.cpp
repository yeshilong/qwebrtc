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

#include "rtcvideoencodervp9.h"
#include "rtcwrappednativevideoencoder.h"

#include "absl/container/inlined_vector.h"
#include "api/video_codecs/sdp_video_format.h"
#include "modules/video_coding/codecs/vp9/include/vp9.h"
#include "modules/video_coding/svc/create_scalability_structure.h"

RTCVideoEncoderVP9::RTCVideoEncoderVP9(QObject *parent) : QObject{parent}
{
}

IRTCVideoEncoder *RTCVideoEncoderVP9::vp9Encoder()
{
    std::unique_ptr<webrtc::VideoEncoder> nativeEncoder(webrtc::VP9Encoder::Create());
    if (!nativeEncoder)
    {
        return nullptr;
    }
    return new RTCWrappedNativeVideoEncoder{std::move(nativeEncoder)};
}

bool RTCVideoEncoderVP9::isSupported()
{
#if defined(RTC_ENABLE_VP9)
    return true;
#else
    return false;
#endif
}

QVector<QString> RTCVideoEncoderVP9::scalabilityModes()
{
    QVector<QString> scalabilityModes;
    for (const auto &scalabilityMode : webrtc::kAllScalabilityModes)
    {
        if (webrtc::ScalabilityStructureConfig(scalabilityMode).has_value())
        {
            if (webrtc::ScalabilityStructureConfig(scalabilityMode).has_value())
            {
                auto scalabilityModeString = webrtc::ScalabilityModeToString(scalabilityMode);
                scalabilityModes.append(
                    QString::fromUtf8(scalabilityModeString.data(), scalabilityModeString.size()));
            }
        }
    }
    return scalabilityModes;
}
