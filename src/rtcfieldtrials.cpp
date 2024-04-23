#include "rtcfieldtrials.h"

#include <QDebug>

#include "system_wrappers/include/field_trial.h"

QString const& RTCFieldTrialAudioForceABWENoTWCCKey() {
    static QString const key = "WebRTC-Audio-ABWENoTWCC";
    return key;
}

QString const& RTCFieldTrialFlexFec03AdvertisedKey() {
    static QString const key = "WebRTC-FlexFEC-03-Advertised";
    return key;
}

QString const& RTCFieldTrialFlexFec03Key() {
    static QString const key = "WebRTC-FlexFEC-03";
    return key;
}

QString const& RTCFieldTrialH264HighProfileKey() {
    static QString const key = "WebRTC-H264HighProfile";
    return key;
}

QString const& RTCFieldTrialMinimizeResamplingOnMobileKey() {
    static QString const key = "WebRTC-Audio-MinimizeResamplingOnMobile";
    return key;
}

QString const& RTCFieldTrialUseNWPathMonitor() {
    static QString const key = "WebRTC-Network-UseNWPathMonitor";
    return key;
}

QString const& RTCFieldTrialEnabledValue() {
    static QString const value = "Enabled";
    return value;
}

// InitFieldTrialsFromString stores the char*, so the char array must outlive
// the application.
static char *gFieldTrialInitString = nullptr;

RTCFieldTrials::RTCFieldTrials(QObject *parent) : QObject{parent}
{
}

QString RTCFieldTrials::RTCFieldTrialAudioForceABWENoTWCCKey()
{
    return RTCFieldTrialAudioForceABWENoTWCCKey();
}

QString RTCFieldTrials::RTCFieldTrialFlexFec03AdvertisedKey()
{
    return RTCFieldTrialFlexFec03AdvertisedKey();
}

QString RTCFieldTrials::RTCFieldTrialFlexFec03Key()
{
    return RTCFieldTrialFlexFec03Key();
}

QString RTCFieldTrials::RTCFieldTrialH264HighProfileKey()
{
    return RTCFieldTrialH264HighProfileKey();
}

QString RTCFieldTrials::RTCFieldTrialMinimizeResamplingOnMobileKey()
{
    return RTCFieldTrialMinimizeResamplingOnMobileKey();
}

QString RTCFieldTrials::RTCFieldTrialUseNWPathMonitor()
{
    return RTCFieldTrialUseNWPathMonitor();
}

QString RTCFieldTrials::RTCFieldTrialEnabledValue()
{
    return RTCFieldTrialEnabledValue();
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
    gFieldTrialInitString = byteArray.data();
    webrtc::field_trial::InitFieldTrialsFromString(gFieldTrialInitString);
}
