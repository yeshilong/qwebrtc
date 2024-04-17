#ifndef RTCMETRICS_H
#define RTCMETRICS_H

#include <QObject>
#include <QVector>

#include "rtcmetricssampleinfo.h"

/**
 * @brief The RTCMetrics class.
 */
class RTCMetrics : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Enables gathering of metrics (which can be fetched with getAndResetMetrics).
     * Must be called before any other call into WebRTC.
     */
    static void enableMetrics();

    /**
     * @brief Gets and clears native histograms.
     * @return An array of RTCMetricsSampleInfo objects.
     */
    static QVector<RTCMetricsSampleInfo> getAndResetMetrics();

  private:
    static QVector<RTCMetricsSampleInfo> metrics_;
};

#endif // RTCMETRICS_H
