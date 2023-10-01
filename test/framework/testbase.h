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

    ~TestRunResult() {
        testresults.clear();
    }

    int passed() { 
        int count = 0;
        for (const auto& pair : testresults) {
            if (pair.second) {
                ++count;
            }
        }
        return count;
    }

    int failed() {
        int count = 0;
        for (const auto& pair : testresults) {
            if (!pair.second) {
                ++count;
            }
        }
        return count;
    }

    string modulename;

    int total() { return testresults.size(); }

    short score() { 
        int count = total();
        if (count == 0) return 100;
        return ((short) 100 * passed()) / count;
    }

    void add_result(string testname, bool isPassed) {
        testresults[testname] = isPassed;
    }

    private:
        std::unordered_map<std::string, bool> testresults = std::unordered_map<std::string, bool>();
};

class TestBase {
    public:
        TestBase(string testname) {
            name = testname;
        }
        virtual void register_tests() = 0;
        TestRunResult run_all();
        string name;
    protected:
        void add_test(string name, std::function<bool()> implementation);
        bool run_test(string name);
        std::unordered_map<std::string, std::function<bool()>> testfunctions = std::unordered_map<std::string, std::function<bool()>>();
};
#endif