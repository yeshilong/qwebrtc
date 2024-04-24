#include "rtcrtpheaderextension.h"
#include "rtcrtpheaderextension_p.h"

void RTCRtpHeaderExtensionPrivate::init(const webrtc::RtpExtension &nativeRtpExtension)
{
    uri_ = QString::fromStdString(nativeRtpExtension.uri);
    id_ = nativeRtpExtension.id;
    encrypted_ = nativeRtpExtension.encrypt;
}

RTCRtpHeaderExtensionPrivate::RTCRtpHeaderExtensionPrivate()
{
    webrtc::RtpExtension nativeRtpExtension;
    init(nativeRtpExtension);
}

RTCRtpHeaderExtensionPrivate::RTCRtpHeaderExtensionPrivate(
    const webrtc::RtpExtension &nativeRtpExtension)
{
    init(nativeRtpExtension);
}

webrtc::RtpExtension RTCRtpHeaderExtensionPrivate::nativeRtpExtension() const
{
    webrtc::RtpExtension nativeRtpExtension;
    nativeRtpExtension.uri = uri_.toStdString();
    nativeRtpExtension.id = id_;
    nativeRtpExtension.encrypt = encrypted_;
    return nativeRtpExtension;
}

RTCRtpHeaderExtension::RTCRtpHeaderExtension(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpHeaderExtensionPrivate}
{
}

RTCRtpHeaderExtension::RTCRtpHeaderExtension(RTCRtpHeaderExtensionPrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
}

QString RTCRtpHeaderExtension::uri() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->uri_;
}

int RTCRtpHeaderExtension::id() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->id_;
}

bool RTCRtpHeaderExtension::encrypted() const
{
    Q_D(const RTCRtpHeaderExtension);
    return d->encrypted_;
}
