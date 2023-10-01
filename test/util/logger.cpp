#include "logger.h"

//LoggerTests::LoggerTests() : TestBase("LoggerTests") {}

TestRunResult LoggerTests::RunAll() {
    TestRunResult result;
    int passed = 0;
    int testcount = 15;

    result.passed = passed;
    result.failed = testcount - passed;

    return result;
}