#ifndef RTCRTPPARAMETERS_P_H
#define RTCRTPPARAMETERS_P_H

#include <QString>
#include <QVector>
#include <QVariant>

#include "api/rtp_parameters.h"

#include "rtcrtcpparameters.h"
#include "rtcrtpheaderextension.h"
#include "rtcrtpencodingparameters.h"
#include "rtcrtpcodecparameters.h"

class RTCRtpParametersPrivate
{
  public:
    RTCRtpParametersPrivate();
    RTCRtpParametersPrivate(const webrtc::RtpParameters &nativeRtpParameters);
    void init(const webrtc::RtpParameters &nativeRtpParameters);
    webrtc::RtpParameters nativeRtpParameters() const;

    QString transactionId_;
    RTCRtcpParameters *rtcp_;
    QVector<RTCRtpHeaderExtension *> headerExtensions_;
    QVector<RTCRtpEncodingParameters *> encodings_;
    QVector<RTCRtpCodecParameters *> codecs_;
    QVariant degradationPreference_;
};

#endif // RTCRTPPARAMETERS_P_H
