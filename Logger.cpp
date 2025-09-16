#include "Logger.h"

void Logger::init() {}

void Logger::log(const String &msg) {
  Serial.println("[LOG] " + msg);
}
