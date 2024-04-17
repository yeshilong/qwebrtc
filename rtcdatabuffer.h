#ifndef RTCDATABUFFER_H
#define RTCDATABUFFER_H

#include <QObject>
#include <QByteArray>

/**
 * @brief The RTCDataBuffer class represents a buffer of data to be sent through a data channel.
 */
class RTCDataBuffer : public QObject
{
    Q_OBJECT
  public:
    explicit RTCDataBuffer(QObject *parent = nullptr);
    RTCDataBuffer(const QByteArray &data, bool isBinary, QObject *parent = nullptr);

    QByteArray data() const;
    bool isBinary() const;

  private:
    QByteArray data_;
    bool isBinary_;
};

#endif // RTCDATABUFFER_H
