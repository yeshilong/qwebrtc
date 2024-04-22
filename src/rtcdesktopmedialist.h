#ifndef RTCDESKTOPMEDIALIST_H
#define RTCDESKTOPMEDIALIST_H

#include <QObject>
#include <QVector>

#include "rtcdesktopsource.h"
#include "rtctypes.h"

/**
 * @brief RTCDesktopMediaList containing various properties and methods.
 */
class RTCDesktopMediaList : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCDesktopMediaList class with the specified type and delegate.
     */
    RTCDesktopMediaList(RTCDesktopSourceType type, QObject *parent = nullptr);

    /**
     * @brief Gets the source type.
     * @return The source type.
     */
    RTCDesktopSourceType sourceType() const;

    /**
     * @brief Updates the source list and returns the result.
     * @return The result.
     */
    int updateSourceList(bool forceReload, bool updateThumbnail);

    /**
     * @brief Gets the sources.
     * @return The sources.
     */
    QVector<RTCDesktopSource *> sources();

  Q_SIGNALS:
    void desktopSourceAdded(RTCDesktopSource *source);
    void desktopSourceRemoved(RTCDesktopSource *source);
    void desktopSourceNameChanged(RTCDesktopSource *source);
    void desktopSourceThumbnailChanged(RTCDesktopSource *source);
};

#endif // RTCDESKTOPMEDIALIST_H
