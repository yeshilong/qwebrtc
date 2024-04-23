#ifndef RTCMETRICSSAMPLEINFO_P_H
#define RTCMETRICSSAMPLEINFO_P_H

#include <QString>
#include <QMap>

#include "system_wrappers/include/metrics.h"

class RTCMetricsSampleInfoPrivate
{
  public:
    RTCMetricsSampleInfoPrivate();
    explicit RTCMetricsSampleInfoPrivate(const webrtc::metrics::SampleInfo &info);

    QString name_;
    int min_;
    int max_;
    int bucketCount_;
    QMap<int, int> samples_;
};

#endif // RTCMETRICSSAMPLEINFO_P_H
