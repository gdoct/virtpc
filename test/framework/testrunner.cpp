#include "testrunner.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::string format_result(const TestRunResult& result) {
  int total = result.passed + result.failed;
  double pass_rate = static_cast<double>(result.passed) / total * 100;
  std::ostringstream output_stream;
  output_stream << result.modulename 
                << " : passed " << result.passed 
                << ", failed " << result.failed
                << " (" << pass_rate << "%)";
  return output_stream.str();
}

void TestRunner::run_all_tests(std::vector<TestBase*> tests)  {
    vector<TestRunResult> results;
    for(auto test: tests) {
      Log::trace("Running tests: " + test->name);
      TestRunResult result = test->run_all();
      results.push_back(result);
    }

  for (auto result: results) {
    auto resultout = format_result(result);
        Log::info(resultout);
  }
}