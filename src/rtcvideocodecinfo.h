#ifndef RTCVIDEOCODECINFO_H
#define RTCVIDEOCODECINFO_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>

class RTCVideoCodecInfoPrivate;
/**
 * @brief Holds information to identify a codec. Corresponds to webrtc::SdpVideoFormat.
 */
class RTCVideoCodecInfo : public QObject
{
  public:
    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name.
     */
    RTCVideoCodecInfo(QObject *parent = nullptr) = delete;

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name.
     */
    RTCVideoCodecInfo(QString name, QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name and parameters.
     */
    RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters, QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name, parameters, and scalability modes.
     */
    RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                      QVector<QString> scalabilityModes, QObject *parent = nullptr);

    /**
     * @brief Determines whether the specified RTCVideoCodecInfo is equal to the current RTCVideoCodecInfo.
     */
    bool isEqualToCodecInfo(RTCVideoCodecInfo info);

    /**
     * @brief Gets the name of the codec.
     * @return The name.
     */
    QString name() const;

    /**
     * @brief Gets the parameters of the codec.
     * @return The parameters.
     */
    QMap<QString, QString> parameters() const;

    /**
     * @brief Gets the scalability modes of the codec.
     * @return The scalability modes.
     */
    QVector<QString> scalabilityModes() const;

  protected:
    RTCVideoCodecInfo(RTCVideoCodecInfoPrivate &d, QObject *parent = nullptr);

  private:
    RTCVideoCodecInfoPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCVideoCodecInfo)
};

#endif // RTCVIDEOCODECINFO_H
