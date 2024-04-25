#include "rtcsessiondescription_p.h"

RTCSessionDescriptionPrivate::RTCSessionDescriptionPrivate(RTCSdpType type, QString sdp)
    : type_(type), sdp_(sdp)
{
}

RTCSessionDescriptionPrivate::RTCSessionDescriptionPrivate(
    const webrtc::SessionDescriptionInterface *nativeSessionDescription)
{
    Q_ASSERT(nativeSessionDescription);
    std::string sdp;
    nativeSessionDescription->ToString(&sdp);
    sdp_ = QString::fromStdString(sdp);
    type_ = static_cast<RTCSdpType>(nativeSessionDescription->GetType());
}

std::unique_ptr<webrtc::SessionDescriptionInterface> RTCSessionDescriptionPrivate::
    nativeSessionDescription() const
{
    webrtc::SdpParseError error;
    std::unique_ptr<webrtc::SessionDescriptionInterface> sessionDescription(
        webrtc::CreateSessionDescription(static_cast<webrtc::SdpType>(type_), sdp_.toStdString(),
                                         &error));

    if (!sessionDescription)
    {
        qFatal("Failed to create session description %s\n line: %s", error.description.c_str(),
               error.line.c_str());
    }

    return sessionDescription;
}

RTCSessionDescription::RTCSessionDescription(RTCSdpType type, QString sdp, QObject *parent)
    : QObject(parent), d_ptr(new RTCSessionDescriptionPrivate(type, sdp))
{
}

RTCSessionDescription::RTCSessionDescription(RTCSessionDescriptionPrivate &d, QObject *parent)
    : QObject(parent), d_ptr(&d)
{
}

RTCSdpType RTCSessionDescription::type() const
{
    Q_D(const RTCSessionDescription);
    return d->type_;
}

QString RTCSessionDescription::sdp() const
{
    Q_D(const RTCSessionDescription);
    return d->sdp_;
}
