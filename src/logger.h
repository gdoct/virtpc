#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

enum LogLevel {         // 08421
    Trace = 1,          // 00001 
    Information = 3,    // 00011
    Warning = 7,        // 00111
    Error = 15          // 01111
};

class Log {
    public:
        static void trace(string message);
        static void info(string message);
        static void warn(string message);
        static void error(string message);

        static void set_LogLevel(LogLevel level);
        static LogLevel get_LogLevel();
};

#endif