#ifndef RTCDATABUFFER_P_H
#define RTCDATABUFFER_P_H

#include <QByteArray>

#include "api/data_channel_interface.h"

class RTCDataBufferPrivate
{
  public:
    RTCDataBufferPrivate(const QByteArray &data, bool isBinary);
    RTCDataBufferPrivate(const webrtc::DataBuffer &nativeDataBuffer);
    const webrtc::DataBuffer *nativeDataBuffer() const;

    QByteArray data() const;
    bool isBinary() const;

  private:
    std::unique_ptr<webrtc::DataBuffer> nativeDataBuffer_;
};

#endif // RTCDATABUFFER_P_H
