#include "logger.h"

bool logger_shouldlog() {
    return true;
}

void LoggerTests::register_tests() {
    UNIT_TEST(logger_shouldlog);
}