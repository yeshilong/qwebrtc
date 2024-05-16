#ifndef RTCLOGGING_H
#define RTCLOGGING_H

#include <QObject>

#include "rtctypes.h"

/**
 * @brief The RTCLogging class.
 */
class RTCLogging : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Logs the log string to the webrtc logstream for the given severity.
     * @param severity The severity.
     * @param logString The log string.
     */
    static void rtcLogEx(RTCLoggingSeverity severity, const QString &logString);

    /**
     * @brief Sets the minimum severity to be logged to console.
     * @param severity The severity.
     */
    static void rtcSetMinDebugLogLevel(RTCLoggingSeverity severity);

    /**
     * @brief Returns the filename with the path prefix removed.
     * @param filePath The file path.
     * @return The filename.
     */
    static QString rtcFileName(const QString &filePath);
};

#define RTCLogString(format, ...)                                                                  \
    QString("(%1:%2 %3): " format)                                                                 \
        .arg(RTCLogging::rtcFileName(QString(__FILE__)))                                           \
        .arg(__LINE__)                                                                             \
        .arg(__FUNCTION__)                                                                         \
        .arg(__VA_ARGS__)

#define RTCLogFormat(severity, format, ...)                                                        \
    do                                                                                             \
    {                                                                                              \
        QString log_string = RTCLogString(format, ##__VA_ARGS__);                                  \
        RTCLogging::rtcLogEx(severity, log_string);                                                \
    } while (false)

#define RTCLogVerbose(format, ...) RTCLogFormat(RTCLoggingSeverity::Verbose, format, ##__VA_ARGS__)

#define RTCLogInfo(format, ...) RTCLogFormat(RTCLoggingSeverity::Info, format, ##__VA_ARGS__)

#define RTCLogWarning(format, ...) RTCLogFormat(RTCLoggingSeverity::Warning, format, ##__VA_ARGS__)

#define RTCLogError(format, ...) RTCLogFormat(RTCLoggingSeverity::Error, format, ##__VA_ARGS__)

#if !defined(NDEBUG)
#define RTCLogDebug(format, ...) RTCLogInfo(format, ##__VA_ARGS__)
#else
#define RTCLogDebug(format, ...)                                                                   \
    do                                                                                             \
    {                                                                                              \
    } while (false)
#endif

#define RTCLog(format, ...) RTCLogInfo(format, ##__VA_ARGS__)

#endif // RTCLOGGING_H
