#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include "../util/logger.h"

using namespace std;

struct TestRunResult {
    int passed;
    int failed;
};

class TestBase {
    public:
        virtual TestRunResult RunAll();
    protected:
        bool run_test(string name, bool (*action)());
        bool assert_equal(Byte b1, Byte b2) { return (b1 == b2);}
        bool assert_equal(Word b1, Word b2) { return (b1 == b2);}
        bool assert_true(bool b) { return b; }
        bool assert_true(std::function<bool()> b) { return b(); }
        bool assert_false(bool b) { return !assert_true(b); }
        bool assert_false(std::function<bool()> b) { return !assert_true(b); }
};

#endif