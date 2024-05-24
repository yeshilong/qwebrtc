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

#ifndef RTCSTATISTICSREPORT_P_H
#define RTCSTATISTICSREPORT_P_H

#include <QMap>

#include "rtcstatisticsreport.h"

#include "api/stats/rtc_stats_report.h"

class RTCStatisticsReportPrivate
{
  public:
    RTCStatisticsReportPrivate(const webrtc::RTCStatsReport &report);

    QDateTime timestampUs_;
    QMap<QString, RTCStatistics *> statistics_;
};

#endif // RTCSTATISTICSREPORT_P_H
