#ifndef RTCRTPTRANSCEIVER_H
#define RTCRTPTRANSCEIVER_H

#include <QObject>
#include <QString>

#include "rtctypes.h"
#include "rtcrtpcodeccapability.h"
#include "rtcrtpreceiver.h"
#include "rtcrtpsender.h"

/**
 * @brief The RTCRtpTransceiver interface.
 */
class IRTCRtpTransceiver
{
  public:
    /**
     * @brief Gets the media type of the transceiver.
     * @return The media type.
     */
    virtual RTCRtpMediaType mediaType() const = 0;

    /**
     * @brief Gets the mid attribute.
     * @return The mid attribute.
     */
    virtual QString mid() const = 0;

    /**
     * @brief Gets the RTCRtpSender corresponding to the RTP media.
     * @return The RTCRtpSender.
     */
    virtual IRTCRtpSender *sender() const = 0;

    /**
     * @brief Gets the RTCRtpReceiver corresponding to the RTP media.
     * @return The RTCRtpReceiver.
     */
    virtual IRTCRtpReceiver *receiver() const = 0;

    /**
     * @brief Checks if the transceiver is stopped.
     * @return True if the transceiver is stopped, false otherwise.
     */
    virtual bool isStopped() const = 0;

    /**
     * @brief Gets the preferred direction of this transceiver.
     * @return The preferred direction.
     */
    virtual RTCRtpTransceiverDirection direction() const = 0;

    /**
     * @brief Gets or sets the codec preferences.
     * @return The codec preferences.
     */
    virtual QVector<RTCRtpCodecCapability> codecPreferences() const = 0;
    virtual void setCodecPreferences(const QVector<RTCRtpCodecCapability> &preferences) = 0;

    /**
     * @brief Gets the current direction negotiated for this transceiver.
     * @return True if the current direction is negotiated, false otherwise.
     */
    virtual bool currentDirection() const = 0;

    /**
     * @brief Stops the RTCRtpTransceiver.
     */
    virtual void stopInternal() = 0;

    /**
     * @brief Sets the direction of the transceiver.
     * @param direction The direction to set.
     */
    virtual void setDirection(RTCRtpTransceiverDirection direction) = 0;
};

/**
 * @brief The RTCRtpTransceiver class.
 */
class RTCRtpTransceiver : public QObject, public IRTCRtpTransceiver
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpTransceiver object.
     */
    explicit RTCRtpTransceiver(QObject *parent = nullptr);
};

#endif // RTCRTPTRANSCEIVER_H
