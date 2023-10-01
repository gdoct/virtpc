#include "testbase.h"

void TestBase::add_test(string name, std::function<bool()> implementation) {
    Log::trace("discovered test: " + name);
    testfunctions[name] = implementation;
}

TestRunResult TestBase::run_all() {
    TestRunResult result = TestRunResult(this->name);
    for (const auto& key: testfunctions) {
        result.add_result(run_test(key.first));
    }
    return result;
}

bool TestBase::run_test(string name) {
    try {
        if (testfunctions.find(name) == testfunctions.end()) {
            Log::warn("test function " + name + " not found.");
            return false;
        }
        auto result = testfunctions[name]();
        if (result) {
            cout << " * \033[32m[SUCCESS] \033[0m" << this->name << "::" << name << endl;
        } else {
            cout << " * \033[0;31m[FAILURE] \033[0m" << this->name << "::" << name << endl;
        }
        return result;
    } catch(int exception) { 
        cout << " * \033[1;31m[CRASHED] \033[0m" << this->name << "::" << name << "" << endl;
    }
    return false;
}