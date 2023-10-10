#include "logger.h"

LogLevel _currentLevel = LogLevel::Information;
std::map<LogLevel, std::string> _logLevelNames = {
                {LogLevel::Trace, "Dbg"},
                {LogLevel::Information, "Inf"},
                {LogLevel::Warning, "Wrn"},
                {LogLevel::Error, "Err"}
            };

bool shouldWrite(LogLevel logLevel) {
    return ((int)logLevel >= (int)_currentLevel);
}

static void write(LogLevel logLevel, std::string* message) {
    if (!shouldWrite(logLevel)) {
        return;
    }
    auto prefix = _logLevelNames[logLevel];
    char time_str[9];
#ifdef _MSC_VER // msvc does not recognize localtime_r
    time_t current_time;
    struct tm local_time;
    time(&current_time);
    localtime_s(&local_time, &current_time);
    strftime(time_str, 9, "%T", &local_time);
#else
    time_t current_time;
    struct tm local_time;
    time(&current_time);
    auto local = localtime_r(&current_time, &local_time);
    strftime(time_str, 9, "%T", local);
#endif
    printf("[%s] %s %s\n", prefix.c_str(), time_str, message->c_str());
}  

void Log::trace(std::string message) {
    write(LogLevel::Trace, &message);
}       

void Log::trace(std::string* message) {
    write(LogLevel::Trace, message);
}       

void Log::info(std::string message) {
    write(LogLevel::Information, &message);
}   

void Log::info(std::string* message) {
    write(LogLevel::Information, message);
}   

void Log::warn(std::string message) {
    write(LogLevel::Warning, &message);
}   

void Log::warn(std::string* message) {
    write(LogLevel::Warning, message);
}   

void Log::error(std::string message) {
    write(LogLevel::Error, &message);
}   

void Log::error(std::string* message) {
    write(LogLevel::Error, message);
} 

void Log::set_LogLevel(LogLevel level) {
    _currentLevel = level;
}

LogLevel Log::get_LogLevel() {
    return _currentLevel;
}
