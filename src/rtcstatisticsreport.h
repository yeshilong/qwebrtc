#ifndef RTCSTATISTICSREPORT_H
#define RTCSTATISTICSREPORT_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QDateTime>

#include "rtcstatistics.h"

/**
 * @brief The RTCStatisticsReport class.
 * A statistics report. Encapsulates a number of RTCStatistics objects.
 */
class RTCStatisticsReport : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCStatisticsReport object.
     */
    explicit RTCStatisticsReport(QObject *parent = nullptr);

    /**
     * @brief Gets the timestamp of the report in microseconds since 1970-01-01T00:00:00Z.
     * @return The timestamp of the report.
     */
    QDateTime timestampUs() const;

    /**
     * @brief Gets the RTCStatistics objects by id.
     * @return The RTCStatistics objects by id.
     */
    QMap<QString, RTCStatistics *> statistics() const;
};

#endif // RTCSTATISTICSREPORT_H
