#ifndef RTCDATACHANNELCONFIGURATION_H
#define RTCDATACHANNELCONFIGURATION_H

#include <QObject>
#include <QString>

class RTCDataChannelConfigurationPrivate;
/**
 * @brief The RTCDataChannelConfiguration class represents a configuration for a data channel with various properties.
 */
class RTCDataChannelConfiguration : public QObject
{
    Q_OBJECT

  public:
    explicit RTCDataChannelConfiguration(QObject *parent = nullptr);

    bool isOrdered() const;
    void setIsOrdered(bool ordered);

    int maxRetransmitTimeMs() const;
    void setMaxRetransmitTimeMs(int time);

    int maxPacketLifeTime() const;
    void setMaxPacketLifeTime(int time);

    int maxRetransmits() const;
    void setMaxRetransmits(int retransmits);

    bool isNegotiated() const;
    void setIsNegotiated(bool negotiated);

    int streamId() const;
    void setStreamId(int id);

    int channelId() const;
    void setChannelId(int id);

    QString protocol() const;
    void setProtocol(const QString &protocol);

  private:
    RTCDataChannelConfigurationPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDataChannelConfiguration)
};

#endif // RTCDATACHANNELCONFIGURATION_H
