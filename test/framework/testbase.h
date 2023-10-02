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
#include "testrunresult.h"

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

#define ASSERT(CONDITION) if (!(CONDITION)) { return false; }
#define ASSERT_FALSE(CONDITION) if (CONDITION) { return false; }
#define ASSERT_NOTNULL(EXPRESSION) if (EXPRESSION == 0) { return false; }

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