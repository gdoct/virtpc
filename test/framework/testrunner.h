#ifndef TEST_FRAMEWORK_TESTRUNNER_H
#define TEST_FRAMEWORK_TESTRUNNER_H

#include "testbase.h"

class TestRunner {
    public:
        static int run_all_tests(std::vector<TestBase*> &tests);
};

#endif