#include <drogon/drogon.h>
#include <filesystem>
#include "util/dotenv.h"

int main() {
  auto& app = drogon::app();
  LOG_INFO << "CWD: " << std::filesystem::current_path().string();
  app.loadConfigFile("./config/drogon.json");
  LOG_INFO << "Server running on http://localhost:8080\n";
  app.run();
}
