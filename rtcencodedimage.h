#ifndef RTCENCODEDIMAGE_H
#define RTCENCODEDIMAGE_H

#include <QObject>
#include <QByteArray>
#include <QSize>

#include "rtctypes.h"

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

    QByteArray Buffer;
    QSize EncodedSize;
    quint32 TimeStamp;
    qint64 CaptureTimeMs;
    qint64 NtpTimeMs;
    quint8 Flags;
    qint64 EncodeStartMs;
    qint64 EncodeFinishMs;
    RTCFrameType FrameType;
    RTCVideoRotation Rotation;
    int Qp;
    RTCVideoContentType ContentType;
};

#endif // RTCENCODEDIMAGE_H
