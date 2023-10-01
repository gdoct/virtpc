#include "testrunner.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::string format_result(TestRunResult& result) {
  std::ostringstream output_stream;
  output_stream << result.modulename 
                << " : passed " << result.passed 
                << ", failed " << result.failed
                << " (" << result.score() << "%)";
  return output_stream.str();
}

void TestRunner::run_all_tests(std::vector<TestBase*> tests)  {
    vector<TestRunResult> results;
    for(auto test: tests) {
      Log::trace("Running tests: " + test->name);
      auto result = test->run_all();
      results.push_back(result);
    }

  for (auto result: results) {
    auto resultout = format_result(result);
        Log::info(resultout);
  }
}