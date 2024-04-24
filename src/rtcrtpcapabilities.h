#ifndef RTCRTPCAPABILITIES_H
#define RTCRTPCAPABILITIES_H

#include <QObject>
#include <QVector>

class RTCRtpCodecCapability;
class RTCRtpCapabilitiesPrivate;
/**
 * @brief The RTCRtpCapabilities class.
 */
class RTCRtpCapabilities : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpCapabilities object.
     */
    explicit RTCRtpCapabilities(QObject *parent = nullptr);

    /**
     * @brief Gets the codecs supported.
     * @return The codecs supported.
     */
    QVector<RTCRtpCodecCapability *> codecs() const;

    // Not implemented.
    // QVector<RtpHeaderExtensionCapability*> headerExtensions;

    // Not implemented.
    // QVector<FecMechanism*> fec;

  protected:
    RTCRtpCapabilities(RTCRtpCapabilitiesPrivate &d, QObject *parent = nullptr);

  private:
    RTCRtpCapabilitiesPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpCapabilities)
};

#endif // RTCRTPCAPABILITIES_H
