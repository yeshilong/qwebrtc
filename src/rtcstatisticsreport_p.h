#ifndef RTCSTATISTICSREPORT_P_H
#define RTCSTATISTICSREPORT_P_H

#include <QMap>

#include "rtcstatisticsreport.h"

#include "api/stats/rtc_stats_report.h"

class RTCStatisticsReportPrivate
{
  public:
    RTCStatisticsReportPrivate(const webrtc::RTCStatsReport &report);

    QDateTime timestampUs_;
    QMap<QString, RTCStatistics *> statistics_;
};

#endif // RTCSTATISTICSREPORT_P_H
