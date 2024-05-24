// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rtcstatistics_p.h"

#include "rtc_base/checks.h"

namespace webrtc
{

/** Converts a single value to a suitable QVariant, QString or QList containing QVariants
  or QStrings, or QMap of QString keys to QVariant values.*/
QVariant ValueFromStatsMember(const RTCStatsMemberInterface *member)
{
    if (member->is_defined())
    {
        switch (member->type())
        {
        case RTCStatsMemberInterface::kBool:
            return QVariant::fromValue<bool>(*member->cast_to<RTCStatsMember<bool>>());
        case RTCStatsMemberInterface::kInt32:
            return QVariant::fromValue<int>(*member->cast_to<RTCStatsMember<int32_t>>());
        case RTCStatsMemberInterface::kUint32:
            return QVariant::fromValue<unsigned int>(*member->cast_to<RTCStatsMember<uint32_t>>());
        case RTCStatsMemberInterface::kInt64:
            return QVariant::fromValue<long>(*member->cast_to<RTCStatsMember<int64_t>>());
        case RTCStatsMemberInterface::kUint64:
            return QVariant::fromValue<unsigned long>(*member->cast_to<RTCStatsMember<uint64_t>>());
        case RTCStatsMemberInterface::kDouble:
            return QVariant::fromValue<double>(*member->cast_to<RTCStatsMember<double>>());
        case RTCStatsMemberInterface::kString:
            return QString::fromStdString(*member->cast_to<RTCStatsMember<std::string>>());
        case RTCStatsMemberInterface::kSequenceBool: {
            std::vector<bool> sequence = *member->cast_to<RTCStatsMember<std::vector<bool>>>();
            QList<QVariant> list;
            for (auto item : sequence)
            {
                list.append(QVariant::fromValue<bool>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceInt32: {
            std::vector<int32_t> sequence =
                *member->cast_to<RTCStatsMember<std::vector<int32_t>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QVariant::fromValue<int>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceUint32: {
            std::vector<uint32_t> sequence =
                *member->cast_to<RTCStatsMember<std::vector<uint32_t>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QVariant::fromValue<unsigned int>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceInt64: {
            std::vector<int64_t> sequence =
                *member->cast_to<RTCStatsMember<std::vector<int64_t>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QVariant::fromValue<long>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceUint64: {
            std::vector<uint64_t> sequence =
                *member->cast_to<RTCStatsMember<std::vector<uint64_t>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QVariant::fromValue<unsigned long>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceDouble: {
            std::vector<double> sequence = *member->cast_to<RTCStatsMember<std::vector<double>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QVariant::fromValue<double>(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kSequenceString: {
            std::vector<std::string> sequence =
                *member->cast_to<RTCStatsMember<std::vector<std::string>>>();
            QList<QVariant> list;
            for (const auto &item : sequence)
            {
                list.append(QString::fromStdString(item));
            }
            return list;
        }
        case RTCStatsMemberInterface::kMapStringUint64: {
            std::map<std::string, uint64_t> map =
                *member->cast_to<RTCStatsMember<std::map<std::string, uint64_t>>>();
            QMap<QString, QVariant> dictionary;
            for (const auto &item : map)
            {
                dictionary.insert(QString::fromStdString(item.first),
                                  QVariant::fromValue<unsigned long>(item.second));
            }
            return dictionary;
        }
        case RTCStatsMemberInterface::kMapStringDouble: {
            std::map<std::string, double> map =
                *member->cast_to<RTCStatsMember<std::map<std::string, double>>>();
            QMap<QString, QVariant> dictionary;
            for (const auto &item : map)
            {
                dictionary.insert(QString::fromStdString(item.first),
                                  QVariant::fromValue<double>(item.second));
            }
            return dictionary;
        }
        default:
            RTC_DCHECK_NOTREACHED();
        }
    }

    return QVariant();
}

} // namespace webrtc

RTCStatisticsPrivate::RTCStatisticsPrivate(const webrtc::RTCStats &stats)
{
    id_ = QString::fromStdString(stats.id());
    timestampUs_ = QDateTime::fromMSecsSinceEpoch(stats.timestamp().us() / 1000);
    type_ = QString::fromStdString(stats.type());

    QMap<QString, QVariant> values;
    for (const webrtc::RTCStatsMemberInterface *member : stats.Members())
    {
        QVariant value = ValueFromStatsMember(member);
        if (value.isValid())
        {
            QString name = QString::fromStdString(member->name());
            Q_ASSERT(name.length() > 0);
            Q_ASSERT(!values.contains(name));
            values[name] = value;
        }
    }
    values_ = values;
}

RTCStatistics::RTCStatistics(RTCStatisticsPrivate &d, QObject *parent) : QObject{parent}, d_ptr{&d}
{
}

QString RTCStatistics::id() const
{
    Q_D(const RTCStatistics);
    return d->id_;
}

QDateTime RTCStatistics::timestampUs() const
{
    Q_D(const RTCStatistics);
    return d->timestampUs_;
}

QString RTCStatistics::type() const
{
    Q_D(const RTCStatistics);
    return d->type_;
}

QMap<QString, QVariant> RTCStatistics::values() const
{
    Q_D(const RTCStatistics);
    return d->values_;
}
