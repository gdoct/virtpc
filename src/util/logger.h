#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <map>
using namespace std;

enum LogLevel : int {   
    Trace       = 0,
    Information = 1,
    Warning     = 2,
    Error       = 3
};

class Log {
    public:
        static void trace(string message);
        static void info(string message);
        static void warn(string message);
        static void error(string message);

        static void trace(string* message);
        static void info(string* message);
        static void warn(string* message);
        static void error(string* message);

        static void set_LogLevel(LogLevel level);
        static LogLevel get_LogLevel();

    private:
       
};

#endif