// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef RTCRTPTRANSCEIVER_H
#define RTCRTPTRANSCEIVER_H

#include <QObject>
#include <QString>

#include "rtctypes.h"
#include "rtcerror.h"
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
    virtual RTCRtpReceiver *receiver() const = 0;

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
    virtual QVector<RTCRtpCodecCapability *> codecPreferences() const = 0;
    virtual void setCodecPreferences(const QVector<RTCRtpCodecCapability *> &preferences) = 0;

    /**
     * @brief Gets the current direction negotiated for this transceiver.
     * @return True if the current direction is negotiated, false otherwise.
     */
    virtual bool currentDirection(RTCRtpTransceiverDirection *currentDirectionOut) const = 0;

    /**
     * @brief Stops the RTCRtpTransceiver.
     */
    virtual void stopInternal() = 0;

    /**
     * @brief Sets the direction of the transceiver.
     * @param direction The direction to set.
     */
    virtual void setDirection(RTCRtpTransceiverDirection direction, RTCError **error) = 0;
};

class RTCRtpTransceiverPrivate;
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

    /**
     * @brief Constructs an RTCRtpTransceiver object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCRtpTransceiver(RTCRtpTransceiverPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the media type of the transceiver.
     * @return The media type.
     */
    RTCRtpMediaType mediaType() const;

    /**
     * @brief Gets the mid attribute.
     * @return The mid attribute.
     */
    QString mid() const;

    /**
     * @brief Gets the RTCRtpSender corresponding to the RTP media.
     * @return The RTCRtpSender.
     */
    IRTCRtpSender *sender() const;

    /**
     * @brief Gets the RTCRtpReceiver corresponding to the RTP media.
     * @return The RTCRtpReceiver.
     */
    RTCRtpReceiver *receiver() const;

    /**
     * @brief Checks if the transceiver is stopped.
     * @return True if the transceiver is stopped, false otherwise.
     */
    bool isStopped() const;

    /**
     * @brief Gets the preferred direction of this transceiver.
     * @return The preferred direction.
     */
    RTCRtpTransceiverDirection direction() const;

    /**
     * @brief Gets or sets the codec preferences.
     * @return The codec preferences.
     */
    QVector<RTCRtpCodecCapability *> codecPreferences() const;
    void setCodecPreferences(const QVector<RTCRtpCodecCapability *> &preferences);

    /**
     * @brief Gets the current direction negotiated for this transceiver.
     * @return True if the current direction is negotiated, false otherwise.
     */
    bool currentDirection(RTCRtpTransceiverDirection *currentDirectionOut) const;

    /**
     * @brief Stops the RTCRtpTransceiver.
     */
    void stopInternal();

    /**
     * @brief Sets the direction of the transceiver.
     * @param direction The direction to set.
     */
    void setDirection(RTCRtpTransceiverDirection direction, RTCError **error);

  private:
    RTCRtpTransceiverPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpTransceiver)
};

#endif // RTCRTPTRANSCEIVER_H
