#include "rtcdtmfsender.h"

RTCDtmfSender::RTCDtmfSender(QObject *parent) : QObject{parent}
{
}

bool RTCDtmfSender::canInsertDtmf() const
{
    return canInsertDtmf_;
}

bool RTCDtmfSender::insertDtmf(const QString &tones, const QTime &duration,
                               const QTime &interToneGap)
{
    return false;
}

QString RTCDtmfSender::remainingTones() const
{
    return remainingTones_;
}

QTime RTCDtmfSender::duration() const
{
    return duration_;
}

QTime RTCDtmfSender::interToneGap() const
{
    return interToneGap_;
}
