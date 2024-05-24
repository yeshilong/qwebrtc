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

#include "rtcyuvhelper.h"

#include "libyuv.h"

void I420Rotate(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                QByteArray &srcV, int srcStrideV, QByteArray &dstY, int dstStrideY,
                QByteArray &dstU, int dstStrideU, QByteArray &dstV, int dstStrideV, QSize size,
                RTCVideoRotation mode)
{
    libyuv::I420Rotate(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                       reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                       reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                       reinterpret_cast<uint8_t *>(dstY.data()), dstStrideY,
                       reinterpret_cast<uint8_t *>(dstU.data()), dstStrideU,
                       reinterpret_cast<uint8_t *>(dstV.data()), dstStrideV, size.width(),
                       size.height(), static_cast<libyuv::RotationMode>(mode));
}
int I420ToNV12(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstY, int dstStrideY, QByteArray &dstUV, int dstStrideUV,
               QSize size)
{
    return libyuv::I420ToNV12(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstY.data()), dstStrideY,
                              reinterpret_cast<uint8_t *>(dstUV.data()), dstStrideUV, size.width(),
                              size.height());
}
int I420ToNV21(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstY, int dstStrideY, QByteArray &dstUV, int dstStrideUV,
               QSize size)
{
    return libyuv::I420ToNV21(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstY.data()), dstStrideY,
                              reinterpret_cast<uint8_t *>(dstUV.data()), dstStrideUV, size.width(),
                              size.height());
}
int I420ToARGB(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstARGB, int dstStrideARGB, QSize size)
{
    return libyuv::I420ToARGB(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstARGB.data()), dstStrideARGB,
                              size.width(), size.height());
}
int I420ToBGRA(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstBGRA, int dstStrideBGRA, QSize size)
{
    return libyuv::I420ToBGRA(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstBGRA.data()), dstStrideBGRA,
                              size.width(), size.height());
}
int I420ToABGR(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstABGR, int dstStrideABGR, QSize size)
{
    return libyuv::I420ToABGR(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstABGR.data()), dstStrideABGR,
                              size.width(), size.height());
}
int I420ToRGBA(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU, QByteArray &srcV,
               int srcStrideV, QByteArray &dstRGBA, int dstStrideRGBA, QSize size)
{
    return libyuv::I420ToRGBA(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                              reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                              reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                              reinterpret_cast<uint8_t *>(dstRGBA.data()), dstStrideRGBA,
                              size.width(), size.height());
}
int I420ToRGB24(QByteArray &srcY, int srcStrideY, QByteArray &srcU, int srcStrideU,
                QByteArray &srcV, int srcStrideV, QByteArray &dstRGB24, int dstStrideRGB24,
                QSize size)
{
    return libyuv::I420ToRGB24(reinterpret_cast<uint8_t *>(srcY.data()), srcStrideY,
                               reinterpret_cast<uint8_t *>(srcU.data()), srcStrideU,
                               reinterpret_cast<uint8_t *>(srcV.data()), srcStrideV,
                               reinterpret_cast<uint8_t *>(dstRGB24.data()), dstStrideRGB24,
                               size.width(), size.height());
}
