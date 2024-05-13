#include "rtcdesktopsource_p.h"

QImage createThumbnailFromNativeSource(const std::vector<unsigned char> &thumbnail)
{
    QByteArray data(reinterpret_cast<const char *>(thumbnail.data()), thumbnail.size());
    QImage image;
    image.loadFromData(data);
    return image;
}

RTCDesktopSourcePrivate::RTCDesktopSourcePrivate()
{
}

RTCDesktopSourcePrivate::RTCDesktopSourcePrivate(webrtc::MediaSource *nativeDesktopSource,
                                                 RTCDesktopSourceType type)
{
    nativeMediaSource_ = nativeDesktopSource;
    sourceId_ = QString::fromStdString(std::to_string(nativeDesktopSource->id()));
    name_ = QString::fromStdString(nativeDesktopSource->name());
    thumbnail_ = createThumbnailFromNativeSource(nativeDesktopSource->thumbnail());
    sourceType_ = type;
}

webrtc::MediaSource *RTCDesktopSourcePrivate::nativeDesktopSource()
{
    return nativeMediaSource_;
}

RTCDesktopSource::RTCDesktopSource(QObject *parent)
    : QObject{parent}, d_ptr{new RTCDesktopSourcePrivate{}}
{
}

RTCDesktopSource::RTCDesktopSource(RTCDesktopSourcePrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCDesktopSource::sourceId() const
{
    Q_D(const RTCDesktopSource);
    return d->sourceId_;
}

QString RTCDesktopSource::name() const
{
    Q_D(const RTCDesktopSource);
    return d->name_;
}

void RTCDesktopSource::setName(const QString &name)
{
    Q_D(RTCDesktopSource);
    d->name_ = name;
}

QImage RTCDesktopSource::thumbnail() const
{
    Q_D(const RTCDesktopSource);
    return d->thumbnail_;
}

void RTCDesktopSource::setThumbnail(const QImage &thumbnail)
{
    Q_D(RTCDesktopSource);
    d->thumbnail_ = thumbnail;
}

RTCDesktopSourceType RTCDesktopSource::sourceType() const
{
    Q_D(const RTCDesktopSource);
    return d->sourceType_;
}

QImage RTCDesktopSource::updateThumbnail()
{
    Q_D(RTCDesktopSource);
    if (d->nativeMediaSource_)
    {
        d->thumbnail_ = createThumbnailFromNativeSource(d->nativeMediaSource_->thumbnail());
    }

    return d->thumbnail_;
}
