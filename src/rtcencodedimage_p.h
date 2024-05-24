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

#ifndef RTCENCODEDIMAGE_P_H
#define RTCENCODEDIMAGE_P_H

#include "rtcencodedimage.h"

#include "api/video/encoded_image.h"

class RTCEncodedImagePrivate
{
  public:
    RTCEncodedImagePrivate();
    RTCEncodedImagePrivate(const webrtc::EncodedImage &nativeEncodedImage);

    webrtc::EncodedImage nativeEncodedImage() const;

    QByteArray buffer_;
    int32_t encodedWidth_;
    int32_t encodedHeight_;
    uint32_t timeStamp_;
    int64_t captureTimeMs_;
    int64_t ntpTimeMs_;
    uint8_t flags_;
    int64_t encodeStartMs_;
    int64_t encodeFinishMs_;
    RTCFrameType frameType_;
    RTCVideoRotation rotation_;
    QVariant qp_;
    RTCVideoContentType contentType_;

    rtc::scoped_refptr<webrtc::EncodedImageBufferInterface> encodedImageBuffer_;
};

#endif // RTCENCODEDIMAGE_P_H
