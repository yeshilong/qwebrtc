#include "rtcssladapter.h"

#include "rtc_base/checks.h"
#include "rtc_base/ssl_adapter.h"

RTCSSLAdapter::RTCSSLAdapter(QObject *parent) : QObject{parent}
{
}

bool RTCSSLAdapter::RTCInitializeSSL()
{
    bool initialized = rtc::InitializeSSL();
    RTC_DCHECK(initialized);
    return initialized;
}

bool RTCSSLAdapter::RTCCleanupSSL()
{
    bool cleanedUp = rtc::CleanupSSL();
    RTC_DCHECK(cleanedUp);
    return cleanedUp;
}
