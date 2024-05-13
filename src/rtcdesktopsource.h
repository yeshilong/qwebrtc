#ifndef RTCDESKTOPSOURCE_H
#define RTCDESKTOPSOURCE_H

#include <QObject>
#include <QString>
#include <QImage>

#include "rtctypes.h"

class RTCDesktopSourcePrivate;
/**
 * @brief The RTCDesktopSource class represents a desktop source, such as the entire screen or a specific window.
 */
class RTCDesktopSource : public QObject
{
    Q_OBJECT

  public:
    explicit RTCDesktopSource(QObject *parent = nullptr);
    RTCDesktopSource(RTCDesktopSourcePrivate &d, QObject *parent = nullptr);

    QString sourceId() const;
    QString name() const;
    QImage thumbnail() const;
    RTCDesktopSourceType sourceType() const;

    QImage updateThumbnail();

  private:
    RTCDesktopSourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDesktopSource)

    void setName(const QString &name);
    void setThumbnail(const QImage &thumbnail);

    friend class RTCDesktopCapturer;
    friend class RTCDesktopMediaList;
    friend class RTCDesktopMediaListPrivate;
};

#endif // RTCDESKTOPSOURCE_H
