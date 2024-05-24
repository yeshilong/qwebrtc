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
    static QVector<RTCMetricsSampleInfo *> getAndResetMetrics();
};

#endif // RTCMETRICS_H
