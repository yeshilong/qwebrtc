#include "rtcmetricssampleinfo.h"

RTCMetricsSampleInfo::RTCMetricsSampleInfo(QObject *parent) : QObject{parent}
{
}

QString RTCMetricsSampleInfo::name() const
{
    return name_;
}

int RTCMetricsSampleInfo::min() const
{
    return min_;
}

int RTCMetricsSampleInfo::max() const
{
    return max_;
}

int RTCMetricsSampleInfo::bucketCount() const
{
    return bucketCount_;
}

QMap<int, int> RTCMetricsSampleInfo::samples() const
{
    return samples_;
}
