#ifndef CNETWORKMONITORFACTORY_H
#define CNETWORKMONITORFACTORY_H

#include <memory>

#include "rtc_base/network_monitor_factory.h"

namespace webrtc {

std::unique_ptr<rtc::NetworkMonitorFactory> CreateNetworkMonitorFactory();

}  // namespace webrtc

#endif  // CNETWORKMONITORFACTORY_H
