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

#include "rtctracing.h"

#include "rtc_base/event_tracer.h"

RTCTracing::RTCTracing(QObject *parent) : QObject{parent}
{
}

void RTCTracing::RTCSetupInternalTracer()
{
    rtc::tracing::SetupInternalTracer();
}

bool RTCTracing::RTCStartInternalCapture(const QString &filePath)
{
    return rtc::tracing::StartInternalCapture(filePath.toStdString());
}

void RTCTracing::RTCStopInternalCapture()
{
    rtc::tracing::StopInternalCapture();
}

void RTCTracing::RTCShutdownInternalTracer()
{
    rtc::tracing::ShutdownInternalTracer();
}
