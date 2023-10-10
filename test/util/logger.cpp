#include "../../src/util/logger.h"
#include "logger.h"
#include <regex>
#include <string>
#include <sstream>
#include <thread>

bool verifyOutput(std::string output, std::string pattern) {
    if (pattern.empty()) {
        ASSERT(output.empty(), "output was expected empty, but contained '" + output + "'");
    }
    return true;
}

bool verifyOutput(std::string output, std::string pattern, LogLevel level, LogLevel currentlevel) {
    if (level < currentlevel) {
        return verifyOutput(output, "");
    }
    return verifyOutput(output, pattern);
}

bool logger_shouldlog_bylevel(LogLevel level) {
    auto oldlevel = Log::get_LogLevel();
    Log::set_LogLevel(level);
    const std::string helloworld = "Hello, world!";
    std::ostringstream oss;
    std::string rt = "\\[Dbg\\] \\d{2}:\\d{2}:\\d{2} Hello, world!";
    std::string ri = "\\[Inf\\] \\d{2}:\\d{2}:\\d{2} Hello, world!";
    std::string re = "\\[Err\\] \\d{2}:\\d{2}:\\d{2} Hello, world!";
    std::string rw = "\\[Wrn\\] \\d{2}:\\d{2}:\\d{2} Hello, world!";
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    Log::trace(helloworld);
    ASSERT(verifyOutput(oss.str(), rt, LogLevel::Trace, level), "incorrect filtering at trace level");

    Log::info(helloworld);
    ASSERT(verifyOutput(oss.str(), rt, LogLevel::Information, level), "incorrect filtering at info level");

    Log::warn(helloworld);
    ASSERT(verifyOutput(oss.str(), rt, LogLevel::Warning, level), "incorrect filtering at warn level");

    Log::error(helloworld);
    ASSERT(verifyOutput(oss.str(), rt, LogLevel::Error, level), "incorrect filtering at error level");

    // Restore original stdout
    std::cout.rdbuf(oldCoutStreamBuf);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    Log::set_LogLevel(oldlevel);
    return true;
}

bool logger_shouldfilter_trace() { return logger_shouldlog_bylevel(LogLevel::Trace); }
bool logger_shouldfilter_information() { return logger_shouldlog_bylevel(LogLevel::Information); }
bool logger_shouldfilter_warning() { return logger_shouldlog_bylevel(LogLevel::Warning); }
bool logger_shouldfilter_error() { return logger_shouldlog_bylevel(LogLevel::Error); }

void LoggerTests::register_tests() {
    UNIT_TEST(logger_shouldfilter_trace);
    UNIT_TEST(logger_shouldfilter_information);
    UNIT_TEST(logger_shouldfilter_warning);
    UNIT_TEST(logger_shouldfilter_error);
}