#include "rtcdesktopsource.h"

RTCDesktopSource::RTCDesktopSource(QObject *parent) : QObject{parent}
{
}

QString RTCDesktopSource::sourceId() const
{
    return sourceId_;
}

QString RTCDesktopSource::name() const
{
    return name_;
}

QImage RTCDesktopSource::thumbnail() const
{
    return thumbnail_;
}

RTCDesktopSourceType RTCDesktopSource::sourceType() const
{
    return sourceType_;
}

QImage RTCDesktopSource::updateThumbnail()
{
    return QImage{};
}
