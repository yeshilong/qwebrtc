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

#include "rtcwrappednativevideodecoder.h"

RTCWrappedNativeVideoDecoder::RTCWrappedNativeVideoDecoder(QObject *parent)
    : IRTCVideoDecoder{parent}
{
}

RTCWrappedNativeVideoDecoder::RTCWrappedNativeVideoDecoder(
    std::unique_ptr<webrtc::VideoDecoder> decoder, QObject *parent)
    : IRTCVideoDecoder{parent}, wrappedDecoder_{std::move(decoder)}
{
}

std::unique_ptr<webrtc::VideoDecoder> RTCWrappedNativeVideoDecoder::releaseWrappedDecoder()
{
    return std::move(wrappedDecoder_);
}

void RTCWrappedNativeVideoDecoder::setCallback(RTCVideoDecoderCallback callback)
{
    RTC_DCHECK_NOTREACHED();
}

int RTCWrappedNativeVideoDecoder::startDecodeWithNumberOfCores(int numberOfCores)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoDecoder::releaseDecoder()
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoDecoder::decode(std::shared_ptr<RTCEncodedImage> encodedImage,
                                         bool missingFrames,
                                         std::shared_ptr<IRTCCodecSpecificInfo> info,
                                         qint64 renderTimeMs)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

QString RTCWrappedNativeVideoDecoder::implementationName() const
{
    RTC_DCHECK_NOTREACHED();
    return QString{};
}
