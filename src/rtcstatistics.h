#ifndef RTCSTATISTICS_H
#define RTCSTATISTICS_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QDateTime>

class RTCStatisticsPrivate;
/**
 * @brief The RTCStatistics class.
 * A part of a report (a subreport) covering a certain area.
 */
class RTCStatistics : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCStatistics object.
     */
    RTCStatistics(QObject *parent = nullptr) = delete;

    /**
     * @brief Gets the id of this subreport, e.g. "RTCMediaStreamTrack_receiver_2".
     * @return The id of this subreport.
     */
    QString id() const;

    /**
     * @brief Gets the timestamp of the subreport in microseconds since 1970-01-01T00:00:00Z.
     * @return The timestamp of the subreport.
     */
    QDateTime timestampUs() const;

    /**
     * @brief Gets the type of the subreport, e.g. "track", "codec".
     * @return The type of the subreport.
     */
    QString type() const;

    /**
     * @brief Gets the keys and values of the subreport, e.g. "totalFramesDuration = 5.551".
     * The values are either NSNumbers or QStrings or QLists encapsulating NSNumbers
     * or QStrings, or QMap of QString keys to QVariant values.
     * @return The keys and values of the subreport.
     */
    QMap<QString, QVariant> values() const;

  protected:
    RTCStatistics(RTCStatisticsPrivate &d, QObject *parent = nullptr);

  private:
    friend class RTCStatisticsReportPrivate;

    RTCStatisticsPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCStatistics)
};

#endif // RTCSTATISTICS_H
