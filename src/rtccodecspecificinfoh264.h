#ifndef RTCCODECSPECIFICINFOH264_H
#define RTCCODECSPECIFICINFOH264_H

#include <QObject>

#include "rtctypes.h"
#include "rtccodecspecificinfo.h"

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
};

#endif // RTCCODECSPECIFICINFOH264_H
