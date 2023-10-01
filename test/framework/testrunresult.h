#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include "../../src/util/logger.h"
#include "../../src/core/numbers.h"

struct TestRunResult {
    explicit TestRunResult(const std::string name) : modulename(name) {
    }

    TestRunResult(const TestRunResult& other) : modulename(other.modulename), testresults(other.testresults) {
    }

    const std::string modulename;

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

    int total() { return testresults.size(); }

    short score() { 
        int count = total();
        if (count == 0) return 100;
        return ((short) 100 * passed()) / count;
    }

    void add_result(std::string testname, bool isPassed) {
        testresults[testname] = isPassed;
    }

    private:
        std::unordered_map<std::string, bool> testresults = std::unordered_map<std::string, bool>();
};
