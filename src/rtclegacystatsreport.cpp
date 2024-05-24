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

#include "rtclegacystatsreport_p.h"

RTCLegacyStatsReportPrivate::RTCLegacyStatsReportPrivate()
{
}

RTCLegacyStatsReportPrivate::RTCLegacyStatsReportPrivate(
    const webrtc::StatsReport &nativeStatsReport)
{
    timestamp_ = nativeStatsReport.timestamp();
    type_ = QString::fromStdString(nativeStatsReport.TypeToString());
    reportId_ = QString::fromStdString(nativeStatsReport.id()->ToString());

    QMap<QString, QString> values;
    for (auto const &valuePair : nativeStatsReport.values())
    {
        QString key = QString::fromStdString(valuePair.second->display_name());
        QString value = QString::fromStdString(valuePair.second->ToString());

        // Not expecting duplicate keys.
        Q_ASSERT(!values.contains(key));
        values.insert(key, value);
    }
    values_ = values;
}

RTCLegacyStatsReport::RTCLegacyStatsReport(QObject *parent)
    : QObject{parent}, d_ptr{new RTCLegacyStatsReportPrivate{}}
{
}

RTCLegacyStatsReport::RTCLegacyStatsReport(RTCLegacyStatsReportPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

double RTCLegacyStatsReport::timestamp() const
{
    Q_D(const RTCLegacyStatsReport);
    return d->timestamp_;
}

QString RTCLegacyStatsReport::type() const
{
    Q_D(const RTCLegacyStatsReport);
    return d->type_;
}

QString RTCLegacyStatsReport::reportId() const
{
    Q_D(const RTCLegacyStatsReport);
    return d->reportId_;
}

QMap<QString, QString> RTCLegacyStatsReport::values() const
{
    Q_D(const RTCLegacyStatsReport);
    return d->values_;
}
