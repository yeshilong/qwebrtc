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

#include "rtcdtmfsender.h"
#include "rtcdtmfsender_p.h"

#include "rtc_base/time_utils.h"

RTCDtmfSenderPrivate::RTCDtmfSenderPrivate(
    rtc::scoped_refptr<webrtc::DtmfSenderInterface> dtmfSender)
{
    Q_ASSERT(dtmfSender);
    nativeDtmfSender_ = dtmfSender;
}

rtc::scoped_refptr<webrtc::DtmfSenderInterface> RTCDtmfSenderPrivate::nativeDtmfSender() const
{
    return nativeDtmfSender_;
}

RTCDtmfSender::RTCDtmfSender(QObject *parent)
    : QObject{parent}, d_ptr{new RTCDtmfSenderPrivate{nullptr}}
{
}

RTCDtmfSender::RTCDtmfSender(RTCDtmfSenderPrivate &d, QObject *parent) : QObject{parent}, d_ptr{&d}
{
}

bool RTCDtmfSender::canInsertDtmf() const
{
    Q_D(const RTCDtmfSender);
    return d->nativeDtmfSender_->CanInsertDtmf();
}

bool RTCDtmfSender::insertDtmf(const QString &tones, const QTime &duration,
                               const QTime &interToneGap)
{
    Q_D(RTCDtmfSender);
    int durationMs = static_cast<int>(duration.second() * rtc::kNumMillisecsPerSec);
    int interToneGapMs = static_cast<int>(interToneGap.second() * rtc::kNumMillisecsPerSec);
    return d->nativeDtmfSender_->InsertDtmf(tones.toStdString(), durationMs, interToneGapMs);
}

QString RTCDtmfSender::remainingTones() const
{
    Q_D(const RTCDtmfSender);
    return QString::fromStdString(d->nativeDtmfSender_->tones());
}

QTime RTCDtmfSender::duration() const
{
    Q_D(const RTCDtmfSender);
    QTime duration(0, 0);
    duration = duration.addSecs(d->nativeDtmfSender_->duration());
    return duration;
}

QTime RTCDtmfSender::interToneGap() const
{
    Q_D(const RTCDtmfSender);
    QTime interToneGap(0, 0);
    interToneGap = interToneGap.addSecs(d->nativeDtmfSender_->inter_tone_gap());
    return interToneGap;
}
