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

#ifndef RTCSTATISTICSREPORT_H
#define RTCSTATISTICSREPORT_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QDateTime>

#include "rtcstatistics.h"

class RTCStatisticsReportPrivate;
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
    RTCStatisticsReport(QObject *parent = nullptr) = delete;

    /**
     * @brief Constructs an RTCStatisticsReport object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCStatisticsReport(RTCStatisticsReportPrivate &d, QObject *parent = nullptr);

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

  private:
    RTCStatisticsReportPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCStatisticsReport)
};

#endif // RTCSTATISTICSREPORT_H
