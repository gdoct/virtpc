#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <vector>
#include "../../src/util/logger.h"
#include "../../src/core/numbers.h"

using namespace std;

#define UNIT_TEST(NAME) class NAME : public TestBase {\
    public:\
        NAME() : TestBase(#NAME) {};\
\
        TestRunResult RunAll() override;\
};

struct TestRunResult {
    int passed;
    int failed;
};

class TestBase {
    public:
        TestBase(string testname) {
            name = testname;
        }
        virtual TestRunResult RunAll() = 0;
        static bool assert_equal(Byte b1, Byte b2) { return (b1 == b2);}
        static bool assert_equal(Word b1, Word b2) { return (b1 == b2);}
        static bool assert_true(bool b) { return b; }
        static bool assert_true(std::function<bool()> b) { return b(); }
        static bool assert_false(bool b) { return !assert_true(b); }
        static bool assert_false(std::function<bool()> b) { return !assert_true(b); }
        string name;
};

static bool run_test(string name, bool (*action)()) {
    try {
        auto result = action();
        if (result) {
            cout << "\033[32m[SUCCESS] \033[0m" << name << endl;
        } else {
            cout << "\033[0;31m[FAILURE] \033[0m"<< name << endl;
        }
        return result;
    } catch(int exception) { 
        cout << "\033[1;31m[CRASHED] \033[0m" << name << "" << endl;
    }
    return false;
}
#endif