#include "utility.h"
#include <iostream>

Log::LogLevel Log::m_logLevel;

void Log::SetLevel(LogLevel level) { m_logLevel = level; }

void Log::Error(const char *message) {
    std::cout << "[ Error ] " << message << std::endl;
}

void Log::Warning(const char *message) {
    if (m_logLevel <= levelWarning)
        std::cout << "[ Warning ] " << message << std::endl;
}

void Log::Info(const char *message) {
    if (m_logLevel <= levelInfo)
        std::cout << "[ Info ] " << message << std::endl;
}

void Log::Debug(const char *message) {
    if (m_logLevel <= levelDebug)
        std::cout << "[ Debug ] " << message << std::endl;
}
