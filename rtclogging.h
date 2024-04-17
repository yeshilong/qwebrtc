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

#endif // RTCLOGGING_H
