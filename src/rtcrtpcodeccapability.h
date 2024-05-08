#ifndef RTCRTPCODECCAPABILITY_H
#define RTCRTPCODECCAPABILITY_H

#include <QString>
#include <QMap>
#include <QVariant>

#include "rtctypes.h"

class RTCRtpCodecCapabilityPrivate;
/**
 * @brief The RTCRtpCodecCapability class.
 */
class RTCRtpCodecCapability : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpCodecCapability object.
     */
    explicit RTCRtpCodecCapability(QObject *parent = nullptr);

    /**
     * @brief Gets the MIME "type/subtype" string built from `name` and `kind`.
     * @return The MIME "type/subtype" string.
     */
    QString mimeType() const;

    /**
     * @brief Gets the identifier of the codec, equivalent to MIME subtype.
     * @return The identifier of the codec.
     */
    QString name() const;

    /**
     * @brief Sets the identifier of the codec, equivalent to MIME subtype.
     * @param name The identifier of the codec.
     */
    void setName(const QString &name);

    /**
     * @brief Gets the media type of this codec, equivalent to MIME top-level type.
     * @return The media type of this codec.
     */
    RTCRtpMediaType kind() const;

    /**
     * @brief Sets the media type of this codec, equivalent to MIME top-level type.
     * @param kind The media type of this codec.
     */
    void setKind(const RTCRtpMediaType &kind);

    /**
     * @brief Gets the clock rate in Hertz. If unset, the codec is applicable to any clock rate.
     * @return The clock rate in Hertz.
     */
    QVariant clockRate() const;

    /**
     * @brief Sets the clock rate in Hertz.
     * @param clockRate The clock rate in Hertz.
     */
    void setClockRate(const QVariant &clockRate);

    /**
     * @brief Gets the default payload type for this codec.
     * @return The default payload type for this codec.
     */
    QVariant preferredPayloadType() const;

    /**
     * @brief Sets the default payload type for this codec.
     * @param preferredPayloadType The default payload type for this codec.
     */
    void setPreferredPayloadType(const QVariant &preferredPayloadType);

    /**
     * @brief Gets the number of audio channels supported. Unused for video codecs.
     * @return The number of audio channels supported.
     */
    QVariant numChannels() const;

    /**
     * @brief Sets the number of audio channels supported.
     * @param numChannels The number of audio channels supported.
     */
    void setNumChannels(const QVariant &numChannels);

    /**
     * @brief Gets the codec-specific parameters that must be signaled to the remote party.
     * @return The codec-specific parameters.
     */
    QMap<QString, QString> parameters() const;

    /**
     * @brief Sets the codec-specific parameters that must be signaled to the remote party.
     * @param parameters The codec-specific parameters.
     */
    void setParameters(const QMap<QString, QString> &parameters);

  protected:
    RTCRtpCodecCapability(RTCRtpCodecCapabilityPrivate &d, QObject *parent = nullptr);

    RTCRtpCodecCapabilityPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpCodecCapability)

  private:
    friend class RTCRtpCapabilities;
    friend class RTCRtpTransceiver;
};

#endif // RTCRTPCODECCAPABILITY_H
