#include "rtclogging.h"

#include <QFileInfo>

#include "rtc_base/logging.h"

rtc::LoggingSeverity RTCGetNativeLoggingSeverity(RTCLoggingSeverity severity)
{
    switch (severity)
    {
    case RTCLoggingSeverity::Verbose:
        return rtc::LS_VERBOSE;
    case RTCLoggingSeverity::Info:
        return rtc::LS_INFO;
    case RTCLoggingSeverity::Warning:
        return rtc::LS_WARNING;
    case RTCLoggingSeverity::Error:
        return rtc::LS_ERROR;
    case RTCLoggingSeverity::None:
        return rtc::LS_NONE;
    }
}

void RTCLogging::rtcLogEx(RTCLoggingSeverity severity, const QString &logString)
{
    if (!logString.isEmpty())
    {
        const char *ut8String = logString.toUtf8().constData();
        RTC_LOG_V(RTCGetNativeLoggingSeverity(severity)) << ut8String;
    }
}

void RTCLogging::rtcSetMinDebugLogLevel(RTCLoggingSeverity severity)
{
    rtc::LogMessage::LogToDebug(RTCGetNativeLoggingSeverity(severity));
}

QString RTCLogging::rtcFileName(const QString &filePath)
{
    return QFileInfo(filePath).fileName();
}
