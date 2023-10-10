#ifndef TESTBASE_H
#define TESTBASE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include "../../src/util/logger.h"
#include "../../src/api/numbers.h"
#include "testrunresult.h"

#define UNIT_TEST_CLASS(NAME) class NAME : public TestBase {\
    public:\
        NAME() : TestBase(#NAME) {\
            register_tests();\
        };\
    private:\
        void register_tests() override;\
};

#define UNIT_TEST(testname) add_test(#testname, testname)

#define ASSERT(CONDITION, MESSAGE) if (!(CONDITION)) { Log::error(MESSAGE); return false; }
#define ASSERT_FALSE(CONDITION, MESSAGE) if (CONDITION) { Log::error(MESSAGE); return false; }
#define ASSERT_EQUAL(ARG1, ARG2, MESSAGE) if (ARG1 != ARG2) { Log::error(MESSAGE); return false; }
#define ASSERT_NOTEQUAL(ARG1, ARG2, MESSAGE) if (ARG1 == ARG2) { Log::error(MESSAGE); return false; }
#define ASSERT_NOTNULL(EXPRESSION, MESSAGE) if (EXPRESSION == nullptr) { Log::error(MESSAGE); return false; }

class TestBase {
    public:
        TestBase(std::string testname) {
            name = testname;
        }
        virtual void register_tests() = 0;
        TestRunResult run_all();
        std::string name;
    protected:
        void add_test(std::string name, std::function<bool()> implementation);
        bool run_test(std::string name);
        std::unordered_map<std::string, std::function<bool()>> testfunctions = std::unordered_map<std::string, std::function<bool()>>();
};
#endif