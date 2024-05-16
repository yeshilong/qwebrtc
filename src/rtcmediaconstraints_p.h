#ifndef RTCMEDIACONSTRAINTS_P_H
#define RTCMEDIACONSTRAINTS_P_H

#include "rtcmediaconstraints.h"

#include <QObject>
#include <QMap>

#include "sdk/media_constraints.h"

class RTCMediaConstraintsPrivate
{
  public:
    explicit RTCMediaConstraintsPrivate(QMap<QString, QString> mandatory,
                                        QMap<QString, QString> optional);
    std::unique_ptr<webrtc::MediaConstraints> nativeMediaConstraints();
    webrtc::MediaConstraints::Constraints nativeMediaConstraintsForConstraints(
        QMap<QString, QString> constraints);

  private:
    QMap<QString, QString> mandatory_;
    QMap<QString, QString> optional_;
};

#endif // RTCMEDIACONSTRAINTS_P_H
