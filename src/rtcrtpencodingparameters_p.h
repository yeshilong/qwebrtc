#ifndef RTCRTPENCODINGPARAMETERS_P_H
#define RTCRTPENCODINGPARAMETERS_P_H

#include <QString>
#include <QVariant>

#include "api/rtp_parameters.h"

#include "rtctypes.h"

class RTCRtpEncodingParametersPrivate
{
  public:
    RTCRtpEncodingParametersPrivate();
    RTCRtpEncodingParametersPrivate(
        const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters);
    void init(const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters);

    webrtc::RtpEncodingParameters nativeRtpEncodingParameters() const;

    QString rid_;
    bool isActive_;
    QVariant maxBitrateBps_;
    QVariant minBitrateBps_;
    QVariant maxFramerate_;
    QVariant numTemporalLayers_;
    QVariant scaleResolutionDownBy_;
    QVariant ssrc_;
    double bitratePriority_;
    RTCPriority networkPriority_;
    bool adaptiveAudioPacketTime_;
    QString scalabilityMode_;
};

#endif // RTCRTPENCODINGPARAMETERS_P_H
