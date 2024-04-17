#include "rtcicecandidateerrorevent.h"

RTCIceCandidateErrorEvent::RTCIceCandidateErrorEvent(QObject *parent) : QObject{parent}
{
}

RTCIceCandidateErrorEvent::RTCIceCandidateErrorEvent(const QString &address, int port,
                                                     const QString &url, int errorCode,
                                                     const QString &errorText, QObject *parent)
    : QObject{parent}, address_{address}, port_{port}, url_{url}, errorCode_{errorCode},
      errorText_{errorText}
{
}

QString RTCIceCandidateErrorEvent::address() const
{
    return address_;
}

int RTCIceCandidateErrorEvent::port() const
{
    return port_;
}

QString RTCIceCandidateErrorEvent::url() const
{
    return url_;
}

int RTCIceCandidateErrorEvent::errorCode() const
{
    return errorCode_;
}

QString RTCIceCandidateErrorEvent::errorText() const
{
    return errorText_;
}
