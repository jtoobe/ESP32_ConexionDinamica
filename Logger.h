#pragma once
#include <Arduino.h>

namespace Logger {
  void init();
  void log(const String &msg);
}
