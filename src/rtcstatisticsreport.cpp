#include "rtcstatisticsreport_p.h"
#include "rtcstatistics_p.h"

RTCStatisticsReportPrivate::RTCStatisticsReportPrivate(const webrtc::RTCStatsReport &report)
{
    timestampUs_ = QDateTime::fromMSecsSinceEpoch(report.timestamp().us() / 1000);

    QMap<QString, RTCStatistics *> statisticsById;
    for (const auto &stat : report)
    {
        RTCStatistics *statistics = new RTCStatistics(*new RTCStatisticsPrivate(stat));
        statisticsById.insert(statistics->id(), statistics);
    }
    statistics_ = statisticsById;
}

RTCStatisticsReport::RTCStatisticsReport(RTCStatisticsReportPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QDateTime RTCStatisticsReport::timestampUs() const
{
    Q_D(const RTCStatisticsReport);
    return d->timestampUs_;
}

QMap<QString, RTCStatistics *> RTCStatisticsReport::statistics() const
{
    Q_D(const RTCStatisticsReport);
    return d->statistics_;
}
