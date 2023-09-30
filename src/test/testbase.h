#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include "../util/logger.h"
#include "../core/numbers.h"

using namespace std;

struct TestRunResult {
    int passed;
    int failed;
};

class TestBase {
    public:
        virtual TestRunResult RunAll();
        static bool assert_equal(Byte b1, Byte b2) { return (b1 == b2);}
        static bool assert_equal(Word b1, Word b2) { return (b1 == b2);}
        static bool assert_true(bool b) { return b; }
        static bool assert_true(std::function<bool()> b) { return b(); }
        static bool assert_false(bool b) { return !assert_true(b); }
        static bool assert_false(std::function<bool()> b) { return !assert_true(b); }
    protected:
        bool run_test(string name, bool (*action)());
};

#endif