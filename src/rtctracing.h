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
