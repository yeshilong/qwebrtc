#include "cnetworkmonitorfactory.h"

#if defined(WEBRTC_IOS)
#include "objc_network_monitor.h"
#endif

#include "rtc_base/logging.h"

namespace webrtc
{

std::unique_ptr<rtc::NetworkMonitorFactory> CreateNetworkMonitorFactory()
{
    RTC_DLOG(LS_INFO) << __FUNCTION__;
#if defined(WEBRTC_IOS)
    return std::make_unique<ObjCNetworkMonitorFactory>();
#else
    return nullptr;
#endif
}

}
