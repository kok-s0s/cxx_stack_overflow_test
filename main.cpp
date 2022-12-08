#include "ThreadPool.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include <chrono>
#include <iostream>
#include <plog/Log.h>
#include <string>
#include <vector>

using std::string;

int main() {
  plog::init(plog::debug, "cxx_test.log"); // Step2: initialize the logger

  // Step3: write log messages using a special macro
  // There are several log macros, use the macro you liked the most

  PLOGD << "Hello log!";             // short macro
  PLOG_DEBUG << "Hello log!";        // long macro
  PLOG(plog::debug) << "Hello log!"; // function-style macro

  // Also you can use LOG_XXX macro but it may clash with other logging
  // libraries
  LOGD << "Hello log!";             // short macro
  LOG_DEBUG << "Hello log!";        // long macro
  LOG(plog::debug) << "Hello log!"; // function-style macro

  // create thread pool with 4 worker threads
  ThreadPool pool(4);
  std::vector<std::future<int>> results;

  for (int i = 0; i < 8; ++i) {
    // enqueue and store future
    results.emplace_back(pool.enqueue([i] {
      std::cout << "hello " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "world " << i << std::endl;
      return i * i;
    }));
  }

  for (auto &&result : results)
    // get result from future
    std::cout << result.get() << ' ';
  std::cout << std::endl;

  return 0;
}
