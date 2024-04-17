#ifndef RTCDATACHANNEL_H
#define RTCDATACHANNEL_H

#include <QObject>
#include <QString>
#include <QByteArray>

#include "rtctypes.h"

/**
 * @brief The RTCDataChannel class represents a data channel with various properties and methods.
 */
class RTCDataChannel : public QObject
{
    Q_OBJECT
  public:
    explicit RTCDataChannel(QObject *parent = nullptr);

    QString label() const;
    bool isReliable() const;
    bool isOrdered() const;
    unsigned int maxRetransmitTime() const;
    unsigned short maxPacketLifeTime() const;
    unsigned short maxRetransmits() const;
    QString protocol() const;
    bool isNegotiated() const;
    int streamId() const;
    int channelId() const;
    RTCDataChannelState readyState() const;
    unsigned long long bufferedAmount() const;

    void close();
    bool sendData(const QByteArray &data);

  Q_SIGNALS:
    void dataChannelDidChangeState();
    void dataChannelDidReceiveMessageWithBuffer(const QByteArray &buffer);
    void dataChannelDidChangeBufferedAmount(unsigned long long amount);

  private:
    QString label_;
    bool isReliable_;
    bool isOrdered_;
    unsigned int maxRetransmitTime_;
    unsigned short maxPacketLifeTime_;
    unsigned short maxRetransmits_;
    QString protocol_;
    bool isNegotiated_;
    int streamId_;
    int channelId_;
    RTCDataChannelState readyState_;
    unsigned long long bufferedAmount_;
    QByteArray buffer_;
};

#endif // RTCDATACHANNEL_H
