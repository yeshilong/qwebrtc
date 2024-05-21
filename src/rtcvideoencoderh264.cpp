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

#include "rtcvideoencoderh264.h"

#include "rtcvideocodecinfo_p.h"
#include "rtcwrappednativevideoencoder.h"

#include "modules/video_coding/codecs/h264/include/h264.h"

RTCVideoEncoderH264::RTCVideoEncoderH264(QObject *parent) : QObject{parent}
{
}

IRTCVideoEncoder *RTCVideoEncoderH264::h264Encoder(RTCVideoCodecInfo *codecInfo)
{
    if (codecInfo == nullptr)
    {
        cricket::VideoCodec codec(cricket::kH264CodecName);
        return new RTCWrappedNativeVideoEncoder{
            std::unique_ptr<webrtc::VideoEncoder>(webrtc::H264Encoder::Create(codec))};
    }
    else
    {
        cricket::VideoCodec codec(codecInfo->d_ptr->nativeSdpVideoFormat());
        return new RTCWrappedNativeVideoEncoder{
            std::unique_ptr<webrtc::VideoEncoder>(webrtc::H264Encoder::Create(codec))};
    }
}

bool RTCVideoEncoderH264::isSupported()
{
    return true;
}

QVector<QString> RTCVideoEncoderH264::scalabilityModes()
{
    return QVector<QString>{};
}
