#include "logger.h"

static LogLevel _currentLevel = LogLevel::Information;
static std::map<LogLevel, std::string> _logLevelNames = {
                {LogLevel::Trace, "Trace"},
                {LogLevel::Information, "Information"},
                {LogLevel::Warning, "Warning"},
                {LogLevel::Error, "Error"}
            };

bool shouldWrite(LogLevel logLevel) {
    return ((int)logLevel >= (int)_currentLevel);
}

static void write(LogLevel logLevel, string* message) {
    if (!shouldWrite(logLevel)) {
        return;
    }
    auto prefix = _logLevelNames[logLevel];
    auto now = time(0);
    auto local = localtime(&now);
    char time_str[9];
    strftime(time_str, 9, "%T", local);
    printf("[%s] %s %s\n", prefix.c_str(), time_str, message->c_str());
}  

void Log::trace(string message) {
    write(LogLevel::Trace, &message);
}       

void Log::trace(string* message) {
    write(LogLevel::Trace, message);
}       

void Log::info(string message) {
    write(LogLevel::Information, &message);
}   

void Log::info(string* message) {
    write(LogLevel::Information, message);
}   

void Log::warn(string message) {
    write(LogLevel::Warning, &message);
}   

void Log::warn(string* message) {
    write(LogLevel::Warning, message);
}   

void Log::error(string message) {
    write(LogLevel::Error, &message);
}   

void Log::error(string* message) {
    write(LogLevel::Error, message);
} 

void Log::set_LogLevel(LogLevel level) {
    _currentLevel = level;
}

LogLevel Log::get_LogLevel() {
    return _currentLevel;
}
