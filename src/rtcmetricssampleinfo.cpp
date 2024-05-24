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
