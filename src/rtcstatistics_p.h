#ifndef RTCSTATISTICS_P_H
#define RTCSTATISTICS_P_H

#include "rtcstatistics.h"

#include "api/stats/rtc_stats.h"

#include <QMap>

class RTCStatisticsPrivate
{
  public:
    RTCStatisticsPrivate(const webrtc::RTCStats &stats);

    QString id_;
    QDateTime timestampUs_;
    QString type_;
    QMap<QString, QVariant> values_;
};

#endif // RTCSTATISTICS_P_H
