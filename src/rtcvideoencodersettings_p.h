#ifndef RTCVIDEOENCODERSETTINGS_P_H
#define RTCVIDEOENCODERSETTINGS_P_H

#include "rtcvideoencodersettings.h"

#include "modules/video_coding/include/video_codec_interface.h"

class RTCVideoEncoderSettingsPrivate
{
  public:
    RTCVideoEncoderSettingsPrivate();
    RTCVideoEncoderSettingsPrivate(const webrtc::VideoCodec *nativeVideoCodec);
    webrtc::VideoCodec nativeVideoCodec() const;

    QString name_;
    quint16 width_;
    quint16 height_;
    quint32 startBitrate_;
    quint32 maxBitrate_;
    quint32 minBitrate_;
    quint32 maxFramerate_;
    quint32 qpMax_;
    RTCVideoCodecMode mode_;
};

#endif // RTCVIDEOENCODERSETTINGS_P_H
