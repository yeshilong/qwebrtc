#include "rtcrtcpparameters.h"
#include "rtcrtcpparameters_p.h"

void RTCRtcpParametersPrivate::init(const webrtc::RtcpParameters &nativeRtcpParameters)
{
    cName_ = QString::fromStdString(nativeRtcpParameters.cname);
    isReducedSize_ = nativeRtcpParameters.reduced_size;
}

RTCRtcpParametersPrivate::RTCRtcpParametersPrivate()
{
    webrtc::RtcpParameters nativeRtcpParameters;
    init(nativeRtcpParameters);
}

RTCRtcpParametersPrivate::RTCRtcpParametersPrivate(
    const webrtc::RtcpParameters &nativeRtcpParameters)
{
    init(nativeRtcpParameters);
}

webrtc::RtcpParameters RTCRtcpParametersPrivate::nativeRtcpParameters() const
{
    webrtc::RtcpParameters nativeRtcpParameters;
    nativeRtcpParameters.cname = cName_.toStdString();
    nativeRtcpParameters.reduced_size = isReducedSize_;
    return nativeRtcpParameters;
}

RTCRtcpParameters::RTCRtcpParameters(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtcpParametersPrivate{}}
{
}

RTCRtcpParameters::RTCRtcpParameters(RTCRtcpParametersPrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
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
