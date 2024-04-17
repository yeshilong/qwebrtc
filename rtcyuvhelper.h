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
