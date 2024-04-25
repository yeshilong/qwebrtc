#ifndef RTCDTMFSENDER_H
#define RTCDTMFSENDER_H

#include <QObject>
#include <QString>
#include <QTime>

/**
 * @brief The RTCDtmfSender interface.
 */
class IRTCDtmfSender
{
  public:
    /**
     * @brief Checks if this RTCDtmfSender is capable of sending DTMF.
     * @return True if capable of sending DTMF, false otherwise.
     */
    virtual bool canInsertDtmf() const = 0;

    /**
     * @brief Queues a task that sends the DTMF tones.
     * @param tones The DTMF tones.
     * @param duration The tone duration.
     * @param interToneGap The between-tone gap.
     * @return True if the task was queued successfully, false otherwise.
     */
    virtual bool insertDtmf(const QString &tones, const QTime &duration,
                            const QTime &interToneGap) = 0;

    /**
     * @brief Gets the tones remaining to be played out.
     * @return The remaining tones.
     */
    virtual QString remainingTones() const = 0;

    /**
     * @brief Gets the current tone duration value.
     * @return The tone duration.
     */
    virtual QTime duration() const = 0;

    /**
     * @brief Gets the current value of the between-tone gap.
     * @return The between-tone gap.
     */
    virtual QTime interToneGap() const = 0;
};

class RTCDtmfSenderPrivate;

/**
 * @brief The RTCDtmfSender class.
 */
class RTCDtmfSender : public QObject, public IRTCDtmfSender
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCDtmfSender object.
     */
    explicit RTCDtmfSender(QObject *parent = nullptr);

  public:
    /**
     * @brief Checks if this RTCDtmfSender is capable of sending DTMF.
     * @return True if capable of sending DTMF, false otherwise.
     */
    virtual bool canInsertDtmf() const;

    /**
     * @brief Queues a task that sends the DTMF tones.
     * @param tones The DTMF tones.
     * @param duration The tone duration.
     * @param interToneGap The between-tone gap.
     * @return True if the task was queued successfully, false otherwise.
     */
    virtual bool insertDtmf(const QString &tones, const QTime &duration, const QTime &interToneGap);

    /**
     * @brief Gets the tones remaining to be played out.
     * @return The remaining tones.
     */
    virtual QString remainingTones() const;

    /**
     * @brief Gets the current tone duration value.
     * @return The tone duration.
     */
    virtual QTime duration() const;

    /**
     * @brief Gets the current value of the between-tone gap.
     * @return The between-tone gap.
     */
    virtual QTime interToneGap() const;

  protected:
    RTCDtmfSender(RTCDtmfSenderPrivate &d, QObject *parent = nullptr);

  private:
    friend class RTCRtpSenderPrivate;

    RTCDtmfSenderPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCDtmfSender)
};
#endif // RTCDTMFSENDER_H
