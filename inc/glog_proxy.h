#pragma once

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include "glog/logging.h"

#pragma comment(lib, "glog.lib")

static void InitLog(const char* cmd) {
    FLAGS_logbufsecs = 0;

    google::InitGoogleLogging(cmd);
    google::SetLogDestination(google::GLOG_INFO, "./log_info_");
    google::SetLogDestination(google::GLOG_WARNING, "./log_warning_");
    google::SetLogDestination(google::GLOG_ERROR, "./log_error_");
    google::SetLogDestination(google::GLOG_FATAL, "./log_fatal_");
    // google::SetLogDestination(google::GLOG_INFO, "./log/log_");
    // google::SetLogDestination(google::GLOG_WARNING, "./log/log_");
    // google::SetLogDestination(google::GLOG_ERROR, "./log/log_");
    // google::SetLogDestination(google::GLOG_FATAL, "./log/log_");
}

static void UninitLog() { google::ShutdownGoogleLogging(); }