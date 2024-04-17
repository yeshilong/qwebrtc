#ifndef RTCMEDIASOURCE_H
#define RTCMEDIASOURCE_H

#include <QObject>

#include "rtctypes.h"

/**
 * @brief Represents a media source used for capturing and transmitting audio or video.
 */
class RTCMediaSource : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     */
    explicit RTCMediaSource(QObject *parent = nullptr);

    /**
     * @brief Returns the current state of the RTCMediaSource.
     * @return The current state.
     */
    RTCSourceState state() const;
};

#endif // RTCMEDIASOURCE_H
