#include "rtcmetrics.h"

#include "rtcmetricssampleinfo_p.h"

#include "system_wrappers/include/metrics.h"

void RTCMetrics::enableMetrics()
{
    webrtc::metrics::Enable();
}

QVector<RTCMetricsSampleInfo *> RTCMetrics::getAndResetMetrics()
{
    std::map<std::string, std::unique_ptr<webrtc::metrics::SampleInfo>, rtc::AbslStringViewCmp>
        histograms;
    webrtc::metrics::GetAndReset(&histograms);

    QVector<RTCMetricsSampleInfo *> metrics;
    metrics.reserve(histograms.size());
    for (const auto &histogram : histograms)
    {
        auto metric = new RTCMetricsSampleInfoPrivate(*histogram.second);
        metrics.append(new RTCMetricsSampleInfo(*metric));
    }
    return metrics;
}
