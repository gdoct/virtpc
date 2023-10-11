#include "testrunner.h"
#include <sstream>
#include <string>
#include <vector>

std::string format_result(TestRunResult& result) {
  std::ostringstream output_stream;
  output_stream << result.modulename 
                << " : passed " << result.passed() 
                << ", failed " << result.failed()
                << " (" << result.score() << "%)";
  return output_stream.str();
}

int TestRunner::run_all_tests(std::vector<TestBase*> &tests)  {
  std::vector<TestRunResult> results;
  for(auto test: tests) {
      if (test == nullptr) continue;
      Log::trace("Running tests: " + test->name);
      auto result = test->run_all();
      results.push_back(result);
  }
  int total = 0;
  for (TestRunResult result: results) {
      auto resultout = format_result(result);
      total += result.failed();
      Log::info(resultout);
  }
  return total;
}