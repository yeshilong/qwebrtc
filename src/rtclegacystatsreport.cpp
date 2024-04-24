#include "rtclegacystatsreport.h"
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

RTCLegacyStatsReport::RTCLegacyStatsReport(RTCLegacyStatsReportPrivate &dd, QObject *parent)
    : QObject{parent}, d_ptr{&dd}
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
