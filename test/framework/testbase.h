#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include "../../src/util/logger.h"
#include "../../src/core/numbers.h"

using namespace std;

#define UNIT_TEST(NAME) class NAME : public TestBase {\
    public:\
        TestRunResult RunAll() override;\
};

struct TestRunResult {
    int passed;
    int failed;
};

class TestBase {
    public:
        virtual TestRunResult RunAll() = 0;
        static bool assert_equal(Byte b1, Byte b2) { return (b1 == b2);}
        static bool assert_equal(Word b1, Word b2) { return (b1 == b2);}
        static bool assert_true(bool b) { return b; }
        static bool assert_true(std::function<bool()> b) { return b(); }
        static bool assert_false(bool b) { return !assert_true(b); }
        static bool assert_false(std::function<bool()> b) { return !assert_true(b); }

//         static bool run_test(string name, bool (*action)());
};

static bool run_test(string name, bool (*action)()) {
    try {
        auto result = action();
        if (result) {
            cout << "\033[32m[PASS] \033[0m" << name << endl;
        } else {
            cout << "\033[31m[FAIL] \033[0m"<< name << endl;
        }
        return result;
    } catch(int exception) { 
        /* .. */ 
        cout << "\033[31m[CRASH] " << name << "\033[0m" << endl;
    }
    return false;
}
#endif