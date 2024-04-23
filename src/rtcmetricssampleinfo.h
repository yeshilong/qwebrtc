#ifndef RTCMETRICSSAMPLEINFO_H
#define RTCMETRICSSAMPLEINFO_H

#include <QObject>
#include <QMap>
#include <QString>

class RTCMetricsSampleInfoPrivate;
/**
 * @brief Represents information about a single RTCMetrics sample.
 */
class RTCMetricsSampleInfo : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCMetricsSampleInfo object.
     * @note This constructor is unavailable and will throw a PlatformNotSupportedException if called.
     */
    RTCMetricsSampleInfo(QObject *parent = nullptr);

    /**
     * @brief Gets the name of the histogram.
     * @return The name of the histogram.
     */
    QString name() const;

    /**
     * @brief Gets the minimum bucket value.
     * @return The minimum bucket value.
     */
    int min() const;

    /**
     * @brief Gets the maximum bucket value.
     * @return The maximum bucket value.
     */
    int max() const;

    /**
     * @brief Gets the number of buckets.
     * @return The number of buckets.
     */
    int bucketCount() const;

    /**
     * @brief Gets a map containing the sample values and their corresponding event counts.
     * @return The map of sample values and their event counts.
     */
    QMap<int, int> samples() const;

  protected:
    /**
     * @brief Constructs an RTCMetricsSampleInfo object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCMetricsSampleInfo(RTCMetricsSampleInfoPrivate &d, QObject *parent = nullptr);

  private:
    friend class RTCMetrics;

    Q_DECLARE_PRIVATE(RTCMetricsSampleInfo)
    RTCMetricsSampleInfoPrivate *const d_ptr;
};

#endif // RTCMETRICSSAMPLEINFO_H
