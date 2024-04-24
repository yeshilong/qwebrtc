#ifndef RTCRTPHEADEREXTENSION_H
#define RTCRTPHEADEREXTENSION_H

#include <QObject>
#include <QString>

class RTCRtpHeaderExtensionPrivate;
/**
 * @brief The RTCRtpHeaderExtension class.
 */
class RTCRtpHeaderExtension : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpHeaderExtension object.
     */
    explicit RTCRtpHeaderExtension(QObject *parent = nullptr);

    /**
     * @brief Gets the URI of the RTP header extension.
     * @return The URI of the RTP header extension.
     */
    QString uri() const;

    /**
     * @brief Gets the ID of the RTP header extension.
     * @return The ID of the RTP header extension.
     */
    int id() const;

    /**
     * @brief Gets whether the header extension is encrypted or not.
     * @return True if the header extension is encrypted, false otherwise.
     */
    bool encrypted() const;

  private:
    Q_DECLARE_PRIVATE(RTCRtpHeaderExtension)
    RTCRtpHeaderExtensionPrivate *d_ptr;
};

#endif // RTCRTPHEADEREXTENSION_H
