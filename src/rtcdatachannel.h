#ifndef RTCDATACHANNEL_H
#define RTCDATACHANNEL_H

#include <QObject>
#include <QString>
#include <QByteArray>

#include "rtctypes.h"
#include "rtcdatabuffer.h"

class RTCDataChannelPrivate;
/**
 * @brief The RTCDataChannel class represents a data channel with various properties and methods.
 */
class RTCDataChannel : public QObject
{
    Q_OBJECT
  public:
    ~RTCDataChannel();

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
    bool sendData(const RTCDataBuffer *data);

  Q_SIGNALS:
    void dataChannelDidChangeState();
    void dataChannelDidReceiveMessageWithBuffer(const QByteArray &buffer);
    void dataChannelDidChangeBufferedAmount(unsigned long long amount);

  private:
    RTCDataChannelPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDataChannel)
};

#endif // RTCDATACHANNEL_H
