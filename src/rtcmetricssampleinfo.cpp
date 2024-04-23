#include "rtcmetricssampleinfo.h"
#include "rtcmetricssampleinfo_p.h"

RTCMetricsSampleInfoPrivate::RTCMetricsSampleInfoPrivate()
    : name_{}, min_{0}, max_{0}, bucketCount_{0}, samples_{}
{
}

RTCMetricsSampleInfoPrivate::RTCMetricsSampleInfoPrivate(const webrtc::metrics::SampleInfo &info)
    : name_(QString::fromStdString(info.name)), min_(info.min), max_(info.max),
      bucketCount_(info.bucket_count)
{
    for (const auto &sample : info.samples)
    {
        samples_.insert(sample.first, sample.second);
    }
}

RTCMetricsSampleInfo::RTCMetricsSampleInfo(QObject *parent)
    : QObject{parent}, d_ptr{new RTCMetricsSampleInfoPrivate()}
{
}

RTCMetricsSampleInfo::RTCMetricsSampleInfo(RTCMetricsSampleInfoPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCMetricsSampleInfo::name() const
{
    Q_D(const RTCMetricsSampleInfo);
    return d->name_;
}

int RTCMetricsSampleInfo::min() const
{
    Q_D(const RTCMetricsSampleInfo);
    return d->min_;
}

int RTCMetricsSampleInfo::max() const
{
    Q_D(const RTCMetricsSampleInfo);
    return d->max_;
}

int RTCMetricsSampleInfo::bucketCount() const
{
    Q_D(const RTCMetricsSampleInfo);
    return d->bucketCount_;
}

QMap<int, int> RTCMetricsSampleInfo::samples() const
{
    Q_D(const RTCMetricsSampleInfo);
    return d->samples_;
}
