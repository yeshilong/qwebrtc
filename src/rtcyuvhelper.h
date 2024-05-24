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

#ifndef RTCYUVHELPER_H
#define RTCYUVHELPER_H

#include <QByteArray>
#include <QSize>

#include "rtctypes.h"

/**
 * @brief RTCYUVHelper is a C++ version of webrtc::I420Buffer.
 */
class RTCYUVHelper
{
  public:
    static void I420Rotate(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                           QByteArray &srcV, int srcStrideV, QByteArray &dstY, int dstStrideY,
                           QByteArray &dstU, int dstStrideU, QByteArray &dstV, int dstStrideV,
                           QSize size, RTCVideoRotation mode);
    static int I420ToNV12(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstY, int dstStrideY,
                          QByteArray &dstUV, int dstStrideUV, QSize size);
    static int I420ToNV21(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstY, int dstStrideY,
                          QByteArray &dstUV, int dstStrideUV, QSize size);
    static int I420ToARGB(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstARGB, int dstStrideARGB,
                          QSize size);
    static int I420ToBGRA(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstBGRA, int dstStrideBGRA,
                          QSize size);
    static int I420ToABGR(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstABGR, int dstStrideABGR,
                          QSize size);
    static int I420ToRGBA(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                          QByteArray &srcV, int srcStrideV, QByteArray &dstRGBA, int dstStrideRGBA,
                          QSize size);
    static int I420ToRGB24(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                           QByteArray &srcV, int srcStrideV, QByteArray &dstRGB24,
                           int dstStrideRGB24, QSize size);
};

#endif // RTCYUVHELPER_H
