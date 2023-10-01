#include "testrunner.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::string format_result(const TestRunResult& result) {
  int total = result.passed + result.failed;
  double pass_rate = static_cast<double>(result.passed) / total * 100;
  std::ostringstream output_stream;
  output_stream << "result: passed " << result.passed << ", failed " << result.failed
                << " (" << pass_rate << "%)";
  return output_stream.str();
}

void TestRunner::run_all_tests(std::vector<TestBase*> tests)  {
    for(auto test: tests) {
      Log::info("Running tests: " + test->name);
      auto result = test->RunAll();
      auto resultout = format_result(result);
      if (result.failed > 0) {
          Log::warn("There were failed tests");
      }
      Log::info("Test result: " + resultout);
    }
}