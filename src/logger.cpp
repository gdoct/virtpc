#include "logger.h"

static LogLevel _currentLevel = LogLevel::Information;

static void write(string prefix, string message) {
    // Get the current time
    time_t now = time(0);
    // Convert to localtime
    tm* local = localtime(&now);
    // Format the time as a string
    char time_str[9];
    strftime(time_str, 9, "%T", local);
    // Format the message so it starts with "[prefix]" and the current time
    printf("[%s] %s %s\n", prefix.c_str(), time_str, message.c_str());
  }

void Log::trace(string message) {
    if (_currentLevel >= LogLevel::Trace)
        write("TRACE", message);
}       

void Log::info(string message) {
    if (_currentLevel >= LogLevel::Information)
        write("INFO", message);
}   

void Log::warn(string message) {
    if (_currentLevel >= LogLevel::Warning)
        write("WARNING", message);
}   

void Log::error(string message) {
    if (_currentLevel >= LogLevel::Error)
        write("ERROR", message);
}   

void Log::set_LogLevel(LogLevel level) {
    _currentLevel = level;
}

LogLevel Log::get_LogLevel() {
    return _currentLevel;
}
