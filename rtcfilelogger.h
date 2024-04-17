#ifndef RTCFILELOGGER_H
#define RTCFILELOGGER_H

#include <QObject>
#include <QByteArray>

#include "rtctypes.h"

/**
 * @brief The RTCFileLogger class.
 */
class RTCFileLogger : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCFileLogger object with default settings for dir path, file size and rotation type.
     */
    explicit RTCFileLogger(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCFileLogger object with the specified dir path and file size and default rotation type.
     * @param dirPath The dir path.
     * @param maxFileSize The max file size.
     */
    RTCFileLogger(const QString &dirPath, quint32 maxFileSize, QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCFileLogger object with the specified dir path, file size and rotation type.
     * @param dirPath The dir path.
     * @param maxFileSize The max file size.
     * @param rotationType The rotation type.
     */
    RTCFileLogger(const QString &dirPath, quint32 maxFileSize,
                  RTCFileLoggerRotationType rotationType, QObject *parent = nullptr);

    /**
     * @brief Gets the severity level to capture.
     * @return The severity level to capture.
     */
    RTCFileLoggerSeverity severity() const;

    /**
     * @brief Sets the severity level to capture.
     * @param severity The severity level to capture.
     */
    void setSeverity(RTCFileLoggerSeverity severity);

    /**
     * @brief Gets the rotation type for this file logger.
     * @return The rotation type for this file logger.
     */
    RTCFileLoggerRotationType rotationType() const;

    /**
     * @brief Checks if buffering disk writes is disabled.
     * @return True if buffering disk writes is disabled, false otherwise.
     */
    bool shouldDisableBuffering() const;

    /**
     * @brief Sets whether buffering disk writes should be disabled.
     * @param shouldDisableBuffering True to disable buffering disk writes, false otherwise.
     */
    void setShouldDisableBuffering(bool shouldDisableBuffering);

    /**
     * @brief Starts writing WebRTC logs to disk if not already started. Overwrites any existing file(s).
     */
    void start();

    /**
     * @brief Stops writing WebRTC logs to disk.
     */
    void stop();

    /**
     * @brief Gets the current contents of the logs.
     * @return The current contents of the logs.
     */
    QByteArray logData() const;
};

#endif // RTCFILELOGGER_H
