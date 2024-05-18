#include "rtcfieldtrials.h"

#include <mutex>

#include <QDebug>

#include "system_wrappers/include/field_trial.h"

// InitFieldTrialsFromString stores the char*, so the char array must outlive
// the application.
static char *gFieldTrialInitString = nullptr;
std::mutex fieldTrialLock;

RTCFieldTrials::RTCFieldTrials(QObject *parent) : QObject{parent}
{
}

QString RTCFieldTrials::RTCFieldTrialAudioForceABWENoTWCCKey()
{
    return "WebRTC-Audio-ABWENoTWCC";
}

QString RTCFieldTrials::RTCFieldTrialFlexFec03AdvertisedKey()
{
    return "WebRTC-FlexFEC-03-Advertised";
}

QString RTCFieldTrials::RTCFieldTrialFlexFec03Key()
{
    return "WebRTC-FlexFEC-03";
}

QString RTCFieldTrials::RTCFieldTrialH264HighProfileKey()
{
    return "WebRTC-H264HighProfile";
}

QString RTCFieldTrials::RTCFieldTrialMinimizeResamplingOnMobileKey()
{
    return "WebRTC-Audio-MinimizeResamplingOnMobile";
}

QString RTCFieldTrials::RTCFieldTrialUseNWPathMonitor()
{
    return "WebRTC-Network-UseNWPathMonitor";
}

QString RTCFieldTrials::RTCFieldTrialEnabledValue()
{
    return "Enabled";
}

void RTCFieldTrials::RTCInitFieldTrialDictionary(QMap<QString, QString> fieldTrials)
{
    if (fieldTrials.isEmpty())
    {
        qWarning() << "No fieldTrials provided.";
        return;
    }
    // Assemble the keys and values into the field trial string.
    // We don't perform any extra format checking. That should be done by the underlying WebRTC calls.
    QString fieldTrialInitString;
    for (auto it = fieldTrials.begin(); it != fieldTrials.end(); ++it)
    {
        QString fieldTrialEntry = QString("%1/%2/").arg(it.key(), it.value());
        fieldTrialInitString.append(fieldTrialEntry);
    }
    QByteArray byteArray = fieldTrialInitString.toUtf8();

    // Lock before modifying global variable
    std::lock_guard<std::mutex> lock(fieldTrialLock);

    gFieldTrialInitString = byteArray.data();
    webrtc::field_trial::InitFieldTrialsFromString(gFieldTrialInitString);
}
