#include <iostream>
#include <map>
#include <memory>
#include "testbase.h"

#include "../tests.h"

class TestFactory {
public:
    static std::unique_ptr<TestBase> get_by_name(const std::string& name) {
        if (name == "MemoryTests") {
            return std::make_unique<MemoryTests>();
        } else if (name == "MachineTests") {
            return std::make_unique<MachineTests>();
        } else if (name == "LoggerTests") {
            return std::make_unique<LoggerTests>();
        }
        else if (name == "CpuTests") {
            return std::make_unique<CpuTests>();
        } else {
            return nullptr;
        }
    }
};