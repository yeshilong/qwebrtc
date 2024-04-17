#ifndef RTCDESKTOPSOURCE_H
#define RTCDESKTOPSOURCE_H

#include <QObject>
#include <QString>
#include <QImage>

#include "rtctypes.h"

/**
 * @brief The RTCDesktopSource class represents a desktop source, such as the entire screen or a specific window.
 */
class RTCDesktopSource : public QObject
{
    Q_OBJECT

  public:
    explicit RTCDesktopSource(QObject *parent = nullptr);

    QString sourceId() const;
    QString name() const;
    QImage thumbnail() const;
    RTCDesktopSourceType sourceType() const;

    QImage updateThumbnail();

  private:
    QString sourceId_;
    QString name_;
    QImage thumbnail_;
    RTCDesktopSourceType sourceType_;
};

#endif // RTCDESKTOPSOURCE_H
