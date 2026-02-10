#include "dotenv.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#if defined(_WIN32)
  #include <cstdlib>
  static void setEnv(const std::string& k, const std::string& v) { _putenv_s(k.c_str(), v.c_str()); }
#else
  #include <cstdlib>
  static void setEnv(const std::string& k, const std::string& v) { setenv(k.c_str(), v.c_str(), 0); } // don't overwrite
#endif

static inline void trim(std::string& s) {
  auto notSpace = [](unsigned char c){ return !std::isspace(c); };
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
  s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
}

namespace util {

void loadDotEnv(const std::string& path) {
  std::ifstream in(path);
  if (!in.is_open()) return; 

  std::string line;
  while (std::getline(in, line)) {
    trim(line);
    if (line.empty() || line[0] == '#') continue;

    auto eq = line.find('=');
    if (eq == std::string::npos) continue;

    std::string key = line.substr(0, eq);
    std::string val = line.substr(eq + 1);
    trim(key); trim(val);

    if (val.size() >= 2 && ((val.front() == '"' && val.back() == '"') || (val.front() == '\'' && val.back() == '\''))) {
      val = val.substr(1, val.size() - 2);
    }

    if (!key.empty()) setEnv(key, val);
  }
}

}
