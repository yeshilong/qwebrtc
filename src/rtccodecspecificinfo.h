#ifndef RTCCODECSPECIFICINFO_H
#define RTCCODECSPECIFICINFO_H

#include <QObject>

/**
 * @brief The IRTCCodecSpecificInfo class.
 */
class IRTCCodecSpecificInfo : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCCodecSpecificInfo object.
     */
    explicit IRTCCodecSpecificInfo(QObject *parent = nullptr);
};

#endif // RTCCODECSPECIFICINFO_H
