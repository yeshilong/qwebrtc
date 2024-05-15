#ifndef RTCLEGACYSTATSREPORT_P_H
#define RTCLEGACYSTATSREPORT_P_H

#include <QString>
#include <QMap>

#include "rtclegacystatsreport.h"

#include "api/legacy_stats_types.h"

class RTCLegacyStatsReportPrivate
{
  public:
    RTCLegacyStatsReportPrivate();
    explicit RTCLegacyStatsReportPrivate(const webrtc::StatsReport &nativeStatsReport);

    double timestamp_;
    QString type_;
    QString reportId_;
    QMap<QString, QString> values_;
};

#endif // RTCLEGACYSTATSREPORT_P_H
