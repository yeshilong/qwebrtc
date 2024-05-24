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

#ifndef RTCLEGACYSTATSREPORT_H
#define RTCLEGACYSTATSREPORT_H

#include <QObject>
#include <QMap>

class RTCLegacyStatsReportPrivate;
/**
 * @brief The RTCLegacyStatsReport class.
 */
class RTCLegacyStatsReport : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCLegacyStatsReport object.
     */
    explicit RTCLegacyStatsReport(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCLegacyStatsReport object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCLegacyStatsReport(RTCLegacyStatsReportPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the timestamp.
     * @return The timestamp.
     */
    double timestamp() const;

    /**
     * @brief Gets the type of stats held by this object.
     * @return The type of stats.
     */
    QString type() const;

    /**
     * @brief Gets the identifier for this object.
     * @return The identifier.
     */
    QString reportId() const;

    /**
     * @brief Gets a dictionary holding the actual stats.
     * @return The dictionary holding the actual stats.
     */
    QMap<QString, QString> values() const;

  private:
    RTCLegacyStatsReportPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCLegacyStatsReport)
};

#endif // RTCLEGACYSTATSREPORT_H
