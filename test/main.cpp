#include "../src/util/logger.h"
#include "framework/testrunner.h"
//#include "core/machine.h"
#include "core/mem.h"
#include "util/logger.h"

int main() {
    Log::set_LogLevel(LogLevel::Information);
    Log::info("Running unit tests");
    auto mc = MemoryTests();
    auto lc = LoggerTests();
    //auto mt = MachineTests();
    std::vector<TestBase*> vec { &mc, &lc//, &mt 
    };
    TestRunner::run_all_tests(vec);
}