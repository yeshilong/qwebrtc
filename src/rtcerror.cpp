#include "rtcerror_p.h"

RTCErrorPrivate::RTCErrorPrivate(const webrtc::RTCError &nativeError)
{
    nativeError_ = nativeError;
}

webrtc::RTCError RTCErrorPrivate::nativeError() const
{
    return nativeError_;
}

RTCError::RTCError(QObject *parent) : QObject{parent}
{
}

RTCError::RTCError(RTCErrorPrivate &d, QObject *parent) : QObject{parent}, d_ptr{&d}
{
}

RTCErrorType RTCError::type() const
{
    Q_D(const RTCError);
    return static_cast<RTCErrorType>(d->nativeError_.type());
}

RTCErrorDetailType RTCError::detail() const
{
    Q_D(const RTCError);
    return static_cast<RTCErrorDetailType>(d->nativeError_.error_detail());
}

QString RTCError::message() const
{
    Q_D(const RTCError);
    return QString::fromStdString(d->nativeError_.message());
}

bool RTCError::ok() const
{
    Q_D(const RTCError);
    return d->nativeError_.ok();
}
