#include "rtcrtcpparameters.h"
#include "rtcrtcpparameters_p.h"

RTCRtcpParametersPrivate::RTCRtcpParametersPrivate(
    const webrtc::RtcpParameters &nativeRtcpParameters)
    : cName_{QString::fromStdString(nativeRtcpParameters.cname)},
      isReducedSize_{nativeRtcpParameters.reduced_size}
{
}

RTCRtcpParameters::RTCRtcpParameters(QObject *parent) : QObject{parent}
{
    webrtc::RtcpParameters nativeRtcpParameters;
    d_ptr = new RTCRtcpParametersPrivate(nativeRtcpParameters);
}

QString RTCRtcpParameters::cname() const
{
    Q_D(const RTCRtcpParameters);
    return d->cName_;
}

void RTCRtcpParameters::setCname(const QString &cname)
{
    Q_D(RTCRtcpParameters);
    d->cName_ = cname;
}

bool RTCRtcpParameters::isReducedSize() const
{
    Q_D(const RTCRtcpParameters);
    return d->isReducedSize_;
}

void RTCRtcpParameters::setIsReducedSize(bool isReducedSize)
{
    Q_D(RTCRtcpParameters);
    d->isReducedSize_ = isReducedSize;
}
