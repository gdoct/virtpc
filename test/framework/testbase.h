#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include "../../src/util/logger.h"
#include "../../src/core/numbers.h"

using namespace std;

#define UNIT_TEST_CLASS(NAME) class NAME : public TestBase {\
    public:\
        NAME() : TestBase(#NAME) {\
            register_tests();\
        };\
    private:\
        void register_tests() override;\
};

#define UNIT_TEST(testname) add_test(#testname, testname)

struct TestRunResult {
    TestRunResult(const string name) {
        modulename = name;
    }

    int passed = 0;
    int failed = 0;
    string modulename;

    int total() { return passed + failed; }

    short score() { 
        int count = total();
        if (count == 0) return 0;
        return ((short) 100 * passed) / count;
    }

    void add_result(bool isPassed) {
        if (isPassed) passed++;
        else failed++;
    }
};

class TestBase {
    public:
        TestBase(string testname) {
            name = testname;
        }
        virtual void register_tests() = 0;
        TestRunResult run_all();
        static bool assert_equal(Byte b1, Byte b2) { return (b1 == b2);}
        static bool assert_equal(Word b1, Word b2) { return (b1 == b2);}
        static bool assert_true(bool b) { return b; }
        static bool assert_true(std::function<bool()> b) { return b(); }
        static bool assert_false(bool b) { return !assert_true(b); }
        static bool assert_false(std::function<bool()> b) { return !assert_true(b); }
        string name;
    protected:
        void add_test(string name, std::function<bool()> implementation);
        bool run_test(string name);
        std::unordered_map<std::string, std::function<bool()>> testfunctions = std::unordered_map<std::string, std::function<bool()>>();
};
#endif