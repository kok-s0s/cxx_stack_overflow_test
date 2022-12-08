#include "ThreadPool.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include <chrono>
#include <iostream>
#include <plog/Log.h>
#include <string>
#include <vector>

using std::string;

bool flag = true;

void background_task_01() {
  while (1) {
    while (flag) {
      PLOGD << "thread --- 01 --- running";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    while (!flag) {
      PLOGD << "thread --- 01 --- paused";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
}

void background_task_02() {
  while (1) {
    while (flag) {
      PLOGD << "thread --- 02 --- running";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    while (!flag) {
      PLOGD << "thread --- 02 --- paused";
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
  }
}

void background_task_03() {}

int main() {
  plog::init(plog::debug, "cxx_test.log");

  PLOGD << "Start";

  ThreadPool pool(2);

  pool.enqueue(background_task_01);
  pool.enqueue(background_task_02);

  while (1) {
    PLOGD << "main thread";
    flag = !flag;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }

  PLOGD << "End";

  return 0;
}
