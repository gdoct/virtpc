#include "testbase.h"
std::unordered_map<std::string, std::function<bool()>> testfunctions = std::unordered_map<std::string, std::function<bool()>>();

void TestBase::add_test(string name, std::function<bool()> implementation) {
    testfunctions[name] = implementation;
}