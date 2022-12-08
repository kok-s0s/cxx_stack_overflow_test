#include "ThreadPool.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include <chrono>
#include <iostream>
#include <plog/Log.h>
#include <string>
#include <vector>

// #define LEN 1 * 1024 * 1024
#define LEN 512 * 1024

using std::string;

void background_task_01() {
  int size = 1;
  PLOGD << "thread --- 01 --- 0";
  unsigned char temp[LEN];
  unsigned char temp1[LEN];

  PLOGD << "thread --- 01 --- 1";

  int iCounter = 0;
  while (1) {
    PLOGD << "thread --- 01 --- begin " << iCounter;
    iCounter++;

    memset(temp, 0, LEN);
    memset(temp1, 0, LEN);
    PLOGD << "thread --- 01 --- end " << iCounter << " -- "
          << int(temp[LEN - 1]) << " - " << int(temp1[LEN - 1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  PLOGD << "thread --- 01 --- end";
}

void background_task_02() {
  int iCounter = 0;
  while (1) {
    PLOGD << "thread --- 02 --- begin" << iCounter;
    int itmpV = 0;
    for (int i = 0; i < 100000; ++i) {
      itmpV = i;
    }
    PLOGD << "thread --- 02 --- end" << iCounter;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void background_task_03() {
  int iCounter = 0;
  while (1) {
    PLOGD << "thread --- 03 --- begin" << iCounter;
    int itmpV = 0;
    for (int i = 0; i < 100000; ++i) {
      itmpV = i;
    }
    PLOGD << "thread --- 03 --- end" << iCounter;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void background_task_04() {
  int iCounter = 0;
  while (1) {
    PLOGD << "thread --- 04 --- begin" << iCounter;
    int itmpV = 0;
    for (int i = 0; i < 100000; ++i) {
      itmpV = i;
    }
    PLOGD << "thread --- 04 --- end" << iCounter;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

int main() {
  plog::init(plog::debug, "cxx_test.log");

  PLOGD << "Start";

  ThreadPool pool(4);

  pool.enqueue(background_task_01);
  pool.enqueue(background_task_02);
  pool.enqueue(background_task_03);
  pool.enqueue(background_task_04);

  while (1) {
    PLOGD << "main thread";
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  PLOGD << "End";

  return 0;
}
