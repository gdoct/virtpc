#include "logger.h"

static LogLevel _currentLevel = LogLevel::Information;

static void write(string prefix, string message) {
    time_t now = time(0);
    tm* local = localtime(&now);
    char time_str[9];
    strftime(time_str, 9, "%T", local);
    printf("[%s] %s %s\n", prefix.c_str(), time_str, message.c_str());
  }

bool shouldWrite(LogLevel logLevel) {
    return (logLevel >= _currentLevel);
}

void Log::trace(string message) {
    if (shouldWrite(LogLevel::Trace))
        write("TRACE", message);
}       

void Log::info(string message) {
    if (shouldWrite(LogLevel::Information))
        write("INFO", message);
}   

void Log::warn(string message) {
    if (shouldWrite(LogLevel::Warning))
        write("WARNING", message);
}   

void Log::error(string message) {
    if (shouldWrite(LogLevel::Error))
        write("ERROR", message);
}   

void Log::set_LogLevel(LogLevel level) {
    _currentLevel = level;
}

LogLevel Log::get_LogLevel() {
    return _currentLevel;
}
