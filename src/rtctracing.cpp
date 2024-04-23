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
