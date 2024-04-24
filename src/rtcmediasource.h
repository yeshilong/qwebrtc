#ifndef RTCMEDIASOURCE_H
#define RTCMEDIASOURCE_H

#include <QObject>

#include "rtctypes.h"

class RTCMediaSourcePrivate;

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

  protected:
    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCMediaSource(RTCMediaSourcePrivate &d, QObject *parent = nullptr);

    RTCMediaSourcePrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaSource)
};

#endif // RTCMEDIASOURCE_H
