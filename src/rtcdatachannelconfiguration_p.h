#ifndef RTCDATACHANNELCONFIGURATION_P_H
#define RTCDATACHANNELCONFIGURATION_P_H

#include <QString>

#include "api/data_channel_interface.h"

class RTCDataChannelConfigurationPrivate
{
  public:
    RTCDataChannelConfigurationPrivate();
    webrtc::DataChannelInit nativeDataChannelInit() const;

    webrtc::DataChannelInit nativeDataChannelInit_;
    int maxPacketLifeTime_;
    int channelId_;
};

#endif // RTCDATACHANNELCONFIGURATION_P_H
