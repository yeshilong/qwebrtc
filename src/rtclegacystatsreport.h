#ifndef RTCLEGACYSTATSREPORT_H
#define RTCLEGACYSTATSREPORT_H

#include <QObject>
#include <QMap>

class RTCLegacyStatsReportPrivate;
/**
 * @brief The RTCLegacyStatsReport class.
 */
class RTCLegacyStatsReport : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCLegacyStatsReport object.
     */
    explicit RTCLegacyStatsReport(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCLegacyStatsReport object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCLegacyStatsReport(RTCLegacyStatsReportPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the timestamp.
     * @return The timestamp.
     */
    double timestamp() const;

    /**
     * @brief Gets the type of stats held by this object.
     * @return The type of stats.
     */
    QString type() const;

    /**
     * @brief Gets the identifier for this object.
     * @return The identifier.
     */
    QString reportId() const;

    /**
     * @brief Gets a dictionary holding the actual stats.
     * @return The dictionary holding the actual stats.
     */
    QMap<QString, QString> values() const;

  private:
    RTCLegacyStatsReportPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RTCLegacyStatsReport)
};

#endif // RTCLEGACYSTATSREPORT_H
