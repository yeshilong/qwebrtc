#ifndef RTCCODECSPECIFICINFOH264_H
#define RTCCODECSPECIFICINFOH264_H

#include <QObject>

#include "rtctypes.h"
#include "rtccodecspecificinfo.h"

namespace webrtc
{

namespace
{
class ObjCVideoEncoder;
class ObjCVideoEncoderSelector;
} // namespace

class ObjCVideoDecoderFactory;
class ObjCVideoEncoderFactory;

} // namespace webrtc

class RTCCodecSpecificInfoH264Private;
/**
 * @brief The RTCCodecSpecificInfoH264 class.
 */
class RTCCodecSpecificInfoH264 : public IRTCCodecSpecificInfo
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCCodecSpecificInfoH264 object.
     */
    explicit RTCCodecSpecificInfoH264(QObject *parent = nullptr);

    /**
     * @brief Gets the packetization mode for H264 codec.
     * @return The packetization mode for H264 codec.
     */
    RTCH264PacketizationMode packetizationMode() const;

    /**
     * @brief Sets the packetization mode for H264 codec.
     * @param packetizationMode The packetization mode for H264 codec.
     */
    void setPacketizationMode(RTCH264PacketizationMode packetizationMode);

  private:
    friend class webrtc::ObjCVideoEncoder;

    RTCCodecSpecificInfoH264Private *const d_ptr;
    Q_DECLARE_PRIVATE(RTCCodecSpecificInfoH264)
};

#endif // RTCCODECSPECIFICINFOH264_H
