#ifndef RTCRTPCODECPARAMETERS_P_H
#define RTCRTPCODECPARAMETERS_P_H

#include <QString>
#include <QMap>
#include <QVariant>

#include "api/rtp_parameters.h"

class RTCRtpCodecParametersPrivate
{
  public:
    RTCRtpCodecParametersPrivate();
    RTCRtpCodecParametersPrivate(const webrtc::RtpCodecParameters &nativeRtpCodecParameters);
    void init(const webrtc::RtpCodecParameters &nativeRtpCodecParameters);
    webrtc::RtpCodecParameters nativeRtpCodecParameters() const;

    int payloadType_;
    QString name_;
    QString kind_;
    QVariant clockRate_;
    QVariant numChannels_;
    QMap<QString, QString> parameters_;
};

#endif // RTCRTPCODECPARAMETERS_P_H
