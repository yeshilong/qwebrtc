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

#ifndef RTCRTPENCODINGPARAMETERS_H
#define RTCRTPENCODINGPARAMETERS_H

#include <QObject>
#include <QString>
#include <QVariant>

#include "rtctypes.h"

class RTCRtpEncodingParametersPrivate;
/**
 * @brief The RTCRtpEncodingParameters class.
 */
class RTCRtpEncodingParameters : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpEncodingParameters object.
     */
    explicit RTCRtpEncodingParameters(QObject *parent = nullptr);

    /**
     * @brief Gets the identifier for the encoding layer.
     * @return The identifier for the encoding layer.
     */
    QString rid() const;

    /**
     * @brief Sets the identifier for the encoding layer.
     * @param rid The identifier for the encoding layer.
     */
    void setRid(const QString &rid);

    /**
     * @brief Checks whether the encoding is currently transmitted.
     * @return True if the encoding is currently transmitted, false otherwise.
     */
    bool isActive() const;

    /**
     * @brief Sets whether the encoding is currently transmitted.
     * @param isActive True if the encoding should be transmitted, false otherwise.
     */
    void setIsActive(bool isActive);

    /**
     * @brief Gets the maximum bitrate to use for the encoding.
     * @return The maximum bitrate to use for the encoding, or null if there is no limit.
     */
    QVariant maxBitrateBps() const;

    /**
     * @brief Sets the maximum bitrate to use for the encoding.
     * @param maxBitrateBps The maximum bitrate to use for the encoding, or null if there is no limit.
     */
    void setMaxBitrateBps(const QVariant &maxBitrateBps);

    /**
     * @brief Gets the minimum bitrate to use for the encoding.
     * @return The minimum bitrate to use for the encoding, or null if there is no limit.
     */
    QVariant minBitrateBps() const;

    /**
     * @brief Sets the minimum bitrate to use for the encoding.
     * @param minBitrateBps The minimum bitrate to use for the encoding, or null if there is no limit.
     */
    void setMinBitrateBps(const QVariant &minBitrateBps);

    /**
     * @brief Gets the maximum framerate to use for the encoding.
     * @return The maximum framerate to use for the encoding, or null if there is no limit.
     */
    QVariant maxFramerate() const;

    /**
     * @brief Sets the maximum framerate to use for the encoding.
     * @param maxFramerate The maximum framerate to use for the encoding, or null if there is no limit.
     */
    void setMaxFramerate(const QVariant &maxFramerate);

    /**
     * @brief Gets the requested number of temporal layers to use for the encoding.
     * @return The requested number of temporal layers to use for the encoding, or null if the default should be used.
     */
    QVariant numTemporalLayers() const;

    /**
     * @brief Sets the requested number of temporal layers to use for the encoding.
     * @param numTemporalLayers The requested number of temporal layers to use for the encoding, or null if the default should be used.
     */
    void setNumTemporalLayers(const QVariant &numTemporalLayers);

    /**
     * @brief Gets the scale resolution down by factor.
     * @return The scale resolution down by factor.
     */
    QVariant scaleResolutionDownBy() const;

    /**
     * @brief Sets the scale resolution down by factor.
     * @param scale The scale resolution down by factor.
     */
    void setScaleResolutionDownBy(const QVariant &scale);

    /**
     * @brief Gets the SSRC being used by this encoding.
     * @return The SSRC being used by this encoding.
     */
    QVariant ssrc() const;

    /**
     * @brief Gets the relative bitrate priority.
     * @return The relative bitrate priority.
     */
    double bitratePriority() const;

    /**
     * @brief Sets the relative bitrate priority.
     * @param priority The relative bitrate priority.
     */
    void setBitratePriority(double priority);

    /**
     * @brief Gets the relative DiffServ Code Point priority.
     * @return The relative DiffServ Code Point priority.
     */
    RTCPriority networkPriority() const;

    /**
     * @brief Sets the relative DiffServ Code Point priority.
     * @param priority The relative DiffServ Code Point priority.
     */
    void setNetworkPriority(RTCPriority priority);

    /**
     * @brief Gets the adaptive audio packet time.
     * @return The adaptive audio packet time.
     */
    bool adaptiveAudioPacketTime() const;

    /**
     * @brief Sets the adaptive audio packet time.
     * @param adaptive The adaptive audio packet time.
     */
    void setAdaptiveAudioPacketTime(bool adaptive);

    /**
     * @brief Gets the scalability mode.
     * @return The scalability mode.
     */
    QString scalabilityMode() const;

    /**
     * @brief Sets the scalability mode.
     * @param mode The scalability mode.
     */
    void setScalabilityMode(const QString &mode);

  protected:
    RTCRtpEncodingParameters(RTCRtpEncodingParametersPrivate *d, QObject *parent = nullptr);

    RTCRtpEncodingParametersPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpEncodingParameters)

  private:
    friend class RTCRtpParametersPrivate;
    friend class RTCRtpParameters;
    friend class RTCRtpTransceiverInitPrivate;
};
#endif // RTCRTPENCODINGPARAMETERS_H
