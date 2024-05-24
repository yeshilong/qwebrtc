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

#ifndef RTCTRACING_H
#define RTCTRACING_H

#include <QObject>
#include <QString>

/**
 * @brief The RTCTracing class.
 */
class RTCTracing : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCTracing object.
     */
    explicit RTCTracing(QObject *parent = nullptr);

    /**
     * @brief Setup the internal tracer.
     */
    static void RTCSetupInternalTracer();

    /**
     * @brief Starts capture to specified file. Must be a valid writable path.
     * @param filePath The path to the file where the capture will be stored.
     * @return True if capture starts, false otherwise.
     */
    static bool RTCStartInternalCapture(const QString &filePath);

    /**
     * @brief Stop the internal capture.
     */
    static void RTCStopInternalCapture();

    /**
     * @brief Shutdown the internal tracer.
     */
    static void RTCShutdownInternalTracer();
};

#endif // RTCTRACING_H
