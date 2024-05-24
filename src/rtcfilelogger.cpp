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

#include "rtcfilelogger.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>

#include "rtc_base/checks.h"
#include "rtc_base/log_sinks.h"
#include "rtc_base/logging.h"

const QString kDefaultLogDirName = "webrtc_logs";
const quint64 kDefaultMaxFileSize = 10 * 1024 * 1024; // 10MB.
const char *kRTCFileLoggerRotatingLogPrefix = "rotating_log";
std::unique_ptr<rtc::FileRotatingLogSink> logSink_;

rtc::LoggingSeverity rtcSeverity(RTCFileLoggerSeverity severity)
{
    switch (severity)
    {
    case RTCFileLoggerSeverity::Verbose:
        return rtc::LS_VERBOSE;
    case RTCFileLoggerSeverity::Info:
        return rtc::LS_INFO;
    case RTCFileLoggerSeverity::Warning:
        return rtc::LS_WARNING;
    case RTCFileLoggerSeverity::Error:
        return rtc::LS_ERROR;
    }
    return rtc::LS_NONE;
}

RTCFileLogger::RTCFileLogger(QObject *parent) : QObject{parent}
{
    QStringList paths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString documentsDirPath = paths.first();
    QString defaultDirPath = documentsDirPath + "/" + kDefaultLogDirName;
    init(defaultDirPath, kDefaultMaxFileSize);
}

RTCFileLogger::RTCFileLogger(const QString &dirPath, quint32 maxFileSize, QObject *parent)
    : QObject{parent}
{
    init(dirPath, maxFileSize, RTCFileLoggerRotationType::Call);
}

RTCFileLogger::RTCFileLogger(const QString &dirPath, quint32 maxFileSize,
                             RTCFileLoggerRotationType rotationType, QObject *parent)
    : QObject{parent}
{
    init(dirPath, maxFileSize, rotationType);
}

void RTCFileLogger::init(const QString &dirPath, quint64 maxFileSize,
                         RTCFileLoggerRotationType rotationType)
{
    Q_ASSERT(!dirPath.isEmpty());
    Q_ASSERT(maxFileSize > 0);

    QDir logDir(dirPath);
    if (logDir.exists())
    {
        if (!QFileInfo(dirPath).isDir())
        {
            // Bail if something already exists there.
            return;
        }
    }
    else
    {
        if (!logDir.mkpath(dirPath))
        {
            // Bail if we failed to create a directory.
            return;
        }
    }
    dirPath_ = dirPath;
    maxFileSize_ = maxFileSize;
    severity_ = RTCFileLoggerSeverity::Verbose;
}

RTCFileLogger::~RTCFileLogger()
{
    stop();
}

void RTCFileLogger::start()
{
    if (hasStarted_)
    {
        return;
    }
    switch (rotationType_)
    {
    case RTCFileLoggerRotationType::App:
        logSink_.reset(new rtc::FileRotatingLogSink(dirPath_.toUtf8().constData(),
                                                    kRTCFileLoggerRotatingLogPrefix, maxFileSize_,
                                                    maxFileSize_ / 10));
        break;
    case RTCFileLoggerRotationType::Call:
        logSink_.reset(
            new rtc::CallSessionFileRotatingLogSink(dirPath_.toUtf8().constData(), maxFileSize_));
        break;
    }
    if (!logSink_->Init())
    {
        RTC_LOG(LS_ERROR) << "Failed to open log files at path: " << dirPath_.toUtf8().constData();
        logSink_.reset();
        return;
    }
    if (shouldDisableBuffering_)
    {
        logSink_->DisableBuffering();
    }
    rtc::LogMessage::LogThreads(true);
    rtc::LogMessage::LogTimestamps(true);
    rtc::LogMessage::AddLogToStream(logSink_.get(), rtcSeverity(severity_));
    hasStarted_ = true;
}

void RTCFileLogger::stop()
{
    if (!hasStarted_)
    {
        return;
    }
    RTC_DCHECK(logSink_);
    rtc::LogMessage::RemoveLogToStream(logSink_.get());
    hasStarted_ = false;
    logSink_.reset();
}
