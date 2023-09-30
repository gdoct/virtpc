#include "../src/util/logger.h"
#include "framework/testrunner.h"

int main() {
    Log::info("running unit tests");
    TestRunner::run_all_tests();
    Log::info("done");
}