#ifndef RTCSSLADAPTER_H
#define RTCSSLADAPTER_H

#include <QObject>

/**
 * @brief The RTCSSLAdapter class.
 * Initialize and clean up the SSL library. Failure is fatal.
 * These call the corresponding functions in webrtc/rtc_base/ssladapter.h.
 */
class RTCSSLAdapter : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCSSLAdapter object.
     */
    explicit RTCSSLAdapter(QObject *parent = nullptr);

    /**
     * @brief Initialize the SSL library.
     * @return True if the initialization was successful, false otherwise.
     */
    static bool RTCInitializeSSL();

    /**
     * @brief Clean up the SSL library.
     * @return True if the cleanup was successful, false otherwise.
     */
    static bool RTCCleanupSSL();
};

#endif // RTCSSLADAPTER_H
