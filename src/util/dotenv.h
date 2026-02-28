#pragma once
#include <string>

namespace util::env {
  void loadDotEnv(const std::string& path = "../.env");
}