#ifndef UTIL_LOGGER_H
#define UTIL_LOGGER_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <map>

enum LogLevel : int {   
    Trace       = 0,
    Information = 1,
    Warning     = 2,
    Error       = 3
};

class Log {
    public:
        static void trace(std::string message);
        static void info(std::string message);
        static void warn(std::string message);
        static void error(std::string message);

        static void trace(std::string* message);
        static void info(std::string* message);
        static void warn(std::string* message);
        static void error(std::string* message);

        static void set_LogLevel(LogLevel level);
        static LogLevel get_LogLevel();
};

#endif