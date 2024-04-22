#ifndef RTCCODECSPECIFICINFOH264_P_H
#define RTCCODECSPECIFICINFOH264_P_H

#include <QObject>

#include "modules/video_coding/include/video_codec_interface.h"

#include "rtctypes.h"

class RTCCodecSpecificInfoH264Private
{
  public:
    RTCCodecSpecificInfoH264Private();

    webrtc::CodecSpecificInfo nativeCodecSpecificInfo() const;

    RTCH264PacketizationMode packetizationMode() const;
    void setPacketizationMode(RTCH264PacketizationMode packetizationMode);

  private:
    RTCH264PacketizationMode packetizationMode_;
};

#endif // RTCCODECSPECIFICINFOH264_P_H
