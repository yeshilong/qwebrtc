#ifndef RTCRTCPPARAMETERS_H
#define RTCRTCPPARAMETERS_H

#include <QObject>
#include <QString>

class RTCRtcpParametersPrivate;
/**
 * @brief The RTCRtcpParameters class.
 */
class RTCRtcpParameters : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtcpParameters object.
     */
    explicit RTCRtcpParameters(QObject *parent = nullptr);

    /**
     * @brief Gets the Canonical Name used by RTCP.
     * @return The Canonical Name used by RTCP.
     */
    QString cname() const;

    /**
     * @brief Sets the Canonical Name used by RTCP.
     * @param cname The Canonical Name to be used by RTCP.
     */
    void setCname(const QString &cname);

    /**
     * @brief Checks whether reduced size RTCP is configured or compound RTCP.
     * @return True if reduced size RTCP is configured, false if compound RTCP is configured.
     */
    bool isReducedSize() const;

    /**
     * @brief Sets whether to configure reduced size RTCP or compound RTCP.
     * @param isReducedSize True to configure reduced size RTCP, false to configure compound RTCP.
     */
    void setIsReducedSize(bool isReducedSize);

  private:
    RTCRtcpParametersPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtcpParameters)
};

#endif // RTCRTCPPARAMETERS_H
