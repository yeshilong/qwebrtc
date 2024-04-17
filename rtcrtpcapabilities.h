#ifndef RTCRTPCAPABILITIES_H
#define RTCRTPCAPABILITIES_H

#include "rtcrtpcodeccapability.h"
#include <QObject>
#include <QVector>

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
};

#endif // RTCRTPCAPABILITIES_H
