#ifndef RTCVIDEOENCODERSETTINGS_H
#define RTCVIDEOENCODERSETTINGS_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

class RTCVideoEncoderSettingsPrivate;
/**
 * @brief The RTCVideoEncoderSettings class.
 */
class RTCVideoEncoderSettings : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderSettings object.
     */
    explicit RTCVideoEncoderSettings(QObject *parent = nullptr);

    /**
     * @brief Gets the name.
     * @return The name.
     */
    QString name() const;

    /**
     * @brief Sets the name.
     * @param name The name.
     */
    void setName(const QString &name);

    /**
     * @brief Gets the width.
     * @return The width.
     */
    quint16 width() const;

    /**
     * @brief Sets the width.
     * @param width The width.
     */
    void setWidth(quint16 width);

    /**
     * @brief Gets the height.
     * @return The height.
     */
    quint16 height() const;

    /**
     * @brief Sets the height.
     * @param height The height.
     */
    void setHeight(quint16 height);

    /**
     * @brief Gets the start bitrate in kilobits/sec.
     * @return The start bitrate in kilobits/sec.
     */
    quint32 startBitrate() const;

    /**
     * @brief Sets the start bitrate in kilobits/sec.
     * @param startBitrate The start bitrate in kilobits/sec.
     */
    void setStartBitrate(quint32 startBitrate);

    /**
     * @brief Gets the max bitrate.
     * @return The max bitrate.
     */
    quint32 maxBitrate() const;

    /**
     * @brief Sets the max bitrate.
     * @param maxBitrate The max bitrate.
     */
    void setMaxBitrate(quint32 maxBitrate);

    /**
     * @brief Gets the min bitrate.
     * @return The min bitrate.
     */
    quint32 minBitrate() const;

    /**
     * @brief Sets the min bitrate.
     * @param minBitrate The min bitrate.
     */
    void setMinBitrate(quint32 minBitrate);

    /**
     * @brief Gets the max framerate.
     * @return The max framerate.
     */
    quint32 maxFramerate() const;

    /**
     * @brief Sets the max framerate.
     * @param maxFramerate The max framerate.
     */
    void setMaxFramerate(quint32 maxFramerate);

    /**
     * @brief Gets the QpMax.
     * @return The QpMax.
     */
    quint32 qpMax() const;

    /**
     * @brief Sets the QpMax.
     * @param qpMax The QpMax.
     */
    void setQpMax(quint32 qpMax);

    /**
     * @brief Gets the mode.
     * @return The mode.
     */
    RTCVideoCodecMode mode() const;

    /**
     * @brief Sets the mode.
     * @param mode The mode.
     */
    void setMode(RTCVideoCodecMode mode);

  public:
    /**
     * @brief Constructs an RTCVideoEncoderSettings object.
     * @param d_ptr The private implementation.
     * @param parent The parent object.
     */
    RTCVideoEncoderSettings(RTCVideoEncoderSettingsPrivate &d, QObject *parent = nullptr);

  private:
    RTCVideoEncoderSettingsPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCVideoEncoderSettings)
};
#endif // RTCVIDEOENCODERSETTINGS_H
