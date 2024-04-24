#include "rtcrtpcapabilities.h"
#include "rtcrtpcapabilities_p.h"

#include "rtcrtpcodeccapability.h"
#include "rtcrtpcodeccapability_p.h"

#include "rtc_base/checks.h"
#include "media/base/media_constants.h"

void RTCRtpCapabilitiesPrivate::init(const webrtc::RtpCapabilities &nativeRtpCapabilities)
{
    nativeRtpCapabilities_ = nativeRtpCapabilities;
}

RTCRtpCapabilitiesPrivate::RTCRtpCapabilitiesPrivate()
{
    init(webrtc::RtpCapabilities());
}

RTCRtpCapabilitiesPrivate::RTCRtpCapabilitiesPrivate(
    const webrtc::RtpCapabilities &nativeRtpCapabilities)
{
    init(nativeRtpCapabilities);
}

RTCRtpCapabilities::RTCRtpCapabilities(QObject *parent) : QObject{parent}
{
}

RTCRtpCapabilities::RTCRtpCapabilities(RTCRtpCapabilitiesPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QVector<RTCRtpCodecCapability *> RTCRtpCapabilities::codecs() const
{
    Q_D(const RTCRtpCapabilities);
    QVector<RTCRtpCodecCapability *> result;
    for (const webrtc::RtpCodecCapability &nativeCodecCapability : d->nativeRtpCapabilities_.codecs)
    {
        result.append(
            new RTCRtpCodecCapability(*new RTCRtpCodecCapabilityPrivate(nativeCodecCapability)));
    }
    return result;
}
