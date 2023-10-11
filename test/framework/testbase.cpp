#include "testbase.h"
#include <string>

void TestBase::add_test(std::string name, std::function<bool()> implementation) {
    Log::trace("discovered test: " + name);
    testfunctions[name] = implementation;
}

TestRunResult TestBase::run_all() {
    auto result = TestRunResult(this->name);
    for (const auto& key: testfunctions) {
        std::string testname = key.first;
        result.add_result(testname, run_test(testname));
    }
    return result;
}

bool TestBase::run_test(std::string name) {
    try {
        std::cout << " * " << this->name << "::" << name << "...";
        if (testfunctions.find(name) == testfunctions.end()) {
            std::cout << " ERROR: test function " << name << " not found." << std::endl;
            return false;
        }
        auto result = testfunctions[name]();
        if (result) {
            std::cout << " .. \033[32m[PASS] \033[0m" << std::endl;
        } else {
            std::cout << " * \033[0;31m[FAIL] \033[0m" << std::endl;
        }
        return result;
    } catch(int exception) { 
        std::cout << " * \033[1;31m[CRASH] \033[0m" << std::endl;
    }
    return false;
}