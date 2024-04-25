#ifndef RTCRTPPARAMETERS_H
#define RTCRTPPARAMETERS_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVector>

#include "rtcrtcpparameters.h"
#include "rtcrtpcodecparameters.h"
#include "rtcrtpencodingparameters.h"
#include "rtcrtpheaderextension.h"

class RTCRtpParametersPrivate;
/**
 * @brief The RTCRtpParameters class.
 */
class RTCRtpParameters : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpParameters object.
     */
    explicit RTCRtpParameters(QObject *parent = nullptr);

    /**
     * @brief Gets the transaction ID.
     * @return The transaction ID.
     */
    QString transactionId() const;

    /**
     * @brief Sets the transaction ID.
     * @param id The transaction ID.
     */
    void setTransactionId(const QString &id);

    /**
     * @brief Gets the RTCP parameters.
     * @return The RTCP parameters.
     */
    RTCRtcpParameters *rtcp() const;

    /**
     * @brief Gets the RTP header extensions.
     * @return The RTP header extensions.
     */
    QVector<RTCRtpHeaderExtension *> headerExtensions() const;

    /**
     * @brief Gets the RTP encoding parameters.
     * @return The RTP encoding parameters.
     */
    QVector<RTCRtpEncodingParameters *> encodings() const;

    /**
     * @brief Sets the RTP encoding parameters.
     * @param encodings The RTP encoding parameters.
     */
    void setEncodings(const QVector<RTCRtpEncodingParameters *> &encodings);

    /**
     * @brief Gets the RTP codec parameters.
     * @return The RTP codec parameters.
     */
    QVector<RTCRtpCodecParameters *> codecs() const;

    /**
     * @brief Sets the RTP codec parameters.
     * @param codecs The RTP codec parameters.
     */
    void setCodecs(const QVector<RTCRtpCodecParameters *> &codecs);

    /**
     * @brief Gets the degradation preference.
     * @return The degradation preference.
     */
    QVariant degradationPreference() const;

    /**
     * @brief Sets the degradation preference.
     * @param preference The degradation preference.
     */
    void setDegradationPreference(const QVariant &preference);

  protected:
    RTCRtpParameters(RTCRtpParametersPrivate &d, QObject *parent = nullptr);

  private:
    friend class RTCRtpSender;

    RTCRtpParametersPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpParameters)
};

#endif // RTCRTPPARAMETERS_H
