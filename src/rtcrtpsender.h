#ifndef RTCRTPSENDER_H
#define RTCRTPSENDER_H

#include <QObject>
#include <QString>
#include <QVector>

#include "rtcdtmfsender.h"
#include "rtcmediastreamtrack.h"
#include "rtcrtpparameters.h"

class RTCRtpSenderPrivate;

/**
 * @brief The RTCRtpSender interface.
 */
class IRTCRtpSender
{
  public:
    /**
     * @brief Gets the sender ID.
     * @return The sender ID.
     */
    virtual QString senderId() const = 0;

    /**
     * @brief Gets the RTP parameters.
     * @return The RTP parameters.
     */
    virtual RTCRtpParameters *parameters() const = 0;

    /**
     * @brief Sets the RTP parameters.
     * @param parameters The RTP parameters.
     */
    virtual void setParameters(const RTCRtpParameters &parameters) = 0;

    /**
     * @brief Gets the media stream track.
     * @return The media stream track.
     */
    virtual RTCMediaStreamTrack *track() const = 0;

    /**
     * @brief Sets the media stream track.
     * @param track The media stream track.
     */
    virtual void setTrack(const RTCMediaStreamTrack &track) = 0;

    /**
     * @brief Gets the stream IDs.
     * @return The stream IDs.
     */
    virtual QVector<QString> streamIds() const = 0;

    /**
     * @brief Sets the stream IDs.
     * @param streamIds The stream IDs.
     */
    virtual void setStreamIds(const QVector<QString> &streamIds) = 0;

    /**
     * @brief Gets the DTMF sender.
     * @return The DTMF sender.
     */
    virtual IRTCDtmfSender *dtmfSender() const = 0;
};

/**
 * @brief The RTCRtpSender class.
 */
class RTCRtpSender : public QObject, public IRTCRtpSender
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpSender object.
     */
    explicit RTCRtpSender(QObject *parent = nullptr);

    /**
     * @brief Gets the sender ID.
     * @return The sender ID.
     */
    QString senderId() const;

    /**
     * @brief Gets the RTP parameters.
     * @return The RTP parameters.
     */
    RTCRtpParameters *parameters() const;

    /**
     * @brief Sets the RTP parameters.
     * @param parameters The RTP parameters.
     */
    void setParameters(const RTCRtpParameters &parameters);

    /**
     * @brief Gets the media stream track.
     * @return The media stream track.
     */
    RTCMediaStreamTrack *track() const;

    /**
     * @brief Sets the media stream track.
     * @param track The media stream track.
     */
    void setTrack(const RTCMediaStreamTrack &track);

    /**
     * @brief Gets the stream IDs.
     * @return The stream IDs.
     */
    QVector<QString> streamIds() const;

    /**
     * @brief Sets the stream IDs.
     * @param streamIds The stream IDs.
     */
    void setStreamIds(const QVector<QString> &streamIds);

    /**
     * @brief Gets the DTMF sender.
     * @return The DTMF sender.
     */
    IRTCDtmfSender *dtmfSender() const;

  protected:
    RTCRtpSender(RTCRtpSenderPrivate &d, QObject *parent = nullptr);

  private:
    RTCRtpSenderPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpSender)
};

#endif // RTCRTPSENDER_H
