#include "rtcdtmfsender.h"
#include "rtcdtmfsender_p.h"

#include "rtc_base/time_utils.h"

RTCDtmfSender::RTCDtmfSender(QObject *parent)
    : QObject{parent}, d_ptr{new RTCDtmfSenderPrivate{nullptr}}
{
}

bool RTCDtmfSender::canInsertDtmf() const
{
    Q_D(const RTCDtmfSender);
    return d_ptr->nativeDtmfSender->CanInsertDtmf();
}

bool RTCDtmfSender::insertDtmf(const QString &tones, const QTime &duration,
                               const QTime &interToneGap)
{
    Q_D(RTCDtmfSender);
    int durationMs = static_cast<int>(duration.second() * rtc::kNumMillisecsPerSec);
    int interToneGapMs = static_cast<int>(interToneGap.second() * rtc::kNumMillisecsPerSec);
    return d_ptr->nativeDtmfSender->InsertDtmf(tones.toStdString(), durationMs, interToneGapMs);
}

QString RTCDtmfSender::remainingTones() const
{
    Q_D(const RTCDtmfSender);
    return QString::fromStdString(d_ptr->nativeDtmfSender->tones());
}

QTime RTCDtmfSender::duration() const
{
    Q_D(const RTCDtmfSender);
    QTime duration(0, 0);
    duration = duration.addSecs(d_ptr->nativeDtmfSender->duration());
    return duration;
}

QTime RTCDtmfSender::interToneGap() const
{
    Q_D(const RTCDtmfSender);
    QTime interToneGap(0, 0);
    interToneGap = interToneGap.addSecs(d_ptr->nativeDtmfSender->inter_tone_gap());
    return interToneGap;
}
