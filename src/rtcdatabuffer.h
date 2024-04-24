#ifndef RTCDATABUFFER_H
#define RTCDATABUFFER_H

#include <QObject>
#include <QByteArray>

class RTCDataBufferPrivate;
/**
 * @brief The RTCDataBuffer class represents a buffer of data to be sent through a data channel.
 */
class RTCDataBuffer : public QObject
{
    Q_OBJECT
  public:
    explicit RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent = nullptr);

    QByteArray data() const;
    bool isBinary() const;
    friend class RTCDataChannel;

  protected:
    RTCDataBufferPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCDataBuffer)
};

#endif // RTCDATABUFFER_H
