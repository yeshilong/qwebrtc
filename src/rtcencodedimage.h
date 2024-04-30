#ifndef RTCENCODEDIMAGE_H
#define RTCENCODEDIMAGE_H

#include <QObject>
#include <QByteArray>
#include <QVariant>

#include "rtctypes.h"

class RTCEncodedImagePrivate;

/**
 * @brief Represents an encoded frame. Corresponds to webrtc::EncodedImage.
 */
class RTCEncodedImage : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief RTCEncodedImage constructor.
     * @param parent The parent object.
     */
    explicit RTCEncodedImage(QObject *parent = nullptr);

    QByteArray buffer() const;
    void setBuffer(const QByteArray &buffer);

    int32_t encodedWidth() const;
    void setEncodedWidth(int32_t encodedWidth);

    int32_t encodedHeight() const;
    void setEncodedHeight(int32_t encodedHeight);

    uint32_t timeStamp() const;
    void setTimeStamp(uint32_t timeStamp);

    int64_t captureTimeMs() const;
    void setCaptureTimeMs(int64_t captureTimeMs);

    int64_t ntpTimeMs() const;
    void setNtpTimeMs(int64_t ntpTimeMs);

    uint8_t flags() const;
    void setFlags(uint8_t flags);

    int64_t encodeStartMs() const;
    void setEncodeStartMs(int64_t encodeStartMs);

    int64_t encodeFinishMs() const;
    void setEncodeFinishMs(int64_t encodeFinishMs);

    RTCFrameType frameType() const;
    void setFrameType(const RTCFrameType &frameType);

    RTCVideoRotation rotation() const;
    void setRotation(const RTCVideoRotation &rotation);

    QVariant qp() const;
    void setQp(const QVariant &qp);

    RTCVideoContentType contentType() const;
    void setContentType(const RTCVideoContentType &contentType);

    RTCEncodedImage(RTCEncodedImagePrivate &d, QObject *parent = nullptr);

  private:
    RTCEncodedImagePrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCEncodedImage)
};

#endif // RTCENCODEDIMAGE_H
