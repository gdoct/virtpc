#include <vector>
#include <cctype>
#include "../src/api/constants.h"
#include "../src/util/logger.h"
#include "framework/testrunner.h"
#include "framework/testfactory.h"
#include <filesystem>
#ifdef _MSC_VER
#include "windows.h"
#else
#include <libgen.h>
#endif

std::string get_first_arg(int argc, char* argv[]) {
    if (argc > 1) {
        return std::string(argv[1]);
    } else {
        return "";
    }
}

int run_all_tests() {
    std::vector<std::string> testNames = { "MemoryTests", "MachineTests", "CpuTests", "ClockTests", "InstructionTests", "MicrocodeTests", "ExecutionEngineTests", "LoggerTests" };
    std::vector<TestBase*> tests;
    std::vector<std::unique_ptr<TestBase>> testclassess;

    for (const auto& testName : testNames) {
        auto test = TestFactory::get_by_name(testName);
        testclassess.push_back(std::move(test));
    }

    for (const auto& testclass : testclassess) {
        tests.push_back(testclass.get());
    }
    return TestRunner::run_all_tests(tests);
}

int run_single_test(std::string& testname) {
    auto testc = TestFactory::get_by_name(testname);
    if (testc == nullptr) {
        Log::error("test not found");
        return 1;
    }
    std::vector<TestBase*> vec { testc.get() };
    return TestRunner::run_all_tests(vec);
}

int main(int argc, char* argv[]) {
    Log::set_LogLevel(LogLevel::Information);

#ifdef _MSC_VER
    std::vector<char> executablePath(MAX_PATH);
    DWORD pathLength = GetModuleFileName(NULL, &executablePath[0], executablePath.size());
    if (pathLength == 0) {
        std::cerr << "Error getting executable path" << std::endl;
        return 1;
    } 
    std::string fullPath(executablePath.begin(), executablePath.begin() + pathLength);
    std::filesystem::path directory_path(fullPath);
    auto result = directory_path.remove_filename();
    Paths::set_rootpath(result.string()); 
#else
    char full_path[4096];
    if (realpath(argv[0], full_path) != NULL) {
        std::string executable_path(full_path);
        char* path = dirname(&executable_path[0]);
        std::string directory_path(path);
        Paths::set_rootpath(directory_path);
    }
#endif
    std::string testname = "InstructionTests"; // get_first_arg(argc, argv);
    if (testname == "") {
        Log::info("running all unit tests");
        return run_all_tests();
    } else{
        Log::info("Running unit tests: " + testname);
        return run_single_test(testname);
    }
}