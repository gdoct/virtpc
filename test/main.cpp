#include <vector>
#include <cctype>
#include "../src/util/logger.h"
#include "framework/testrunner.h"
#include "framework/testfactory.h"

using namespace std;

string get_first_arg(int argc, char* argv[]) {
    if (argc > 1) {
        return std::string(argv[1]);
    } else {
        return "";
    }
}

int run_all_tests() {
    vector<string> testNames = { "MemoryTests", "MachineTests", "LoggerTests", "CpuTests", "ClockTests" };
    vector<TestBase*> tests;
    vector<unique_ptr<TestBase>> testclassess;

    for (const auto& testName : testNames) {
        auto test = TestFactory::get_by_name(testName);
        testclassess.push_back(std::move(test));
    }

    for (const auto& testclass : testclassess) {
        tests.push_back(testclass.get());
    }
    return TestRunner::run_all_tests(tests);
}

int run_single_test(string& testname) {
    auto testc = TestFactory::get_by_name(testname);
    if (testc == nullptr) {
        Log::error("test not found");
        return 1;
    }
    vector<TestBase*> vec { testc.get() };
    return TestRunner::run_all_tests(vec);
}

int main(int argc, char* argv[]) {
    Log::set_LogLevel(LogLevel::Information);
    auto testname = get_first_arg(argc, argv);
    if (testname == "") {
        Log::info("running all unit tests");
        return run_all_tests();
    } else{
        Log::info("Running unit tests: " + testname);
        return run_single_test(testname);
    }
}