#include "Config.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Config {

static std::string trim(const std::string& value) {
  auto begin = value.find_first_not_of(" \t\r\n");
  if (begin == std::string::npos) return "";
  auto end = value.find_last_not_of(" \t\r\n");
  return value.substr(begin, end - begin + 1);
}

static void applyEnvironmentOverrides(Config& config) {
  const char* envType = std::getenv("LOG_TYPE");
  if (envType != nullptr) {
    std::string type(envType);
    if (type == "terminal") {
      config.logType = ::Config::LogType::Terminal;
    } else if (type == "file") {
      config.logType = ::Config::LogType::File;
    }
  }

  const char* envDir = std::getenv("LOG_DIRECTORY");
  if (envDir != nullptr && *envDir != '\0') {
    config.logDirectory = envDir;
  }
}

Config loadConfig(const std::filesystem::path& path) {
  Config config;
  std::ifstream stream(path);
  if (stream) {
    std::string line;
    while (std::getline(stream, line)) {
      auto comment = line.find('#');
      if (comment != std::string::npos) line.erase(comment);
      auto equal = line.find('=');
      if (equal == std::string::npos) continue;

      auto key = trim(line.substr(0, equal));
      auto value = trim(line.substr(equal + 1));
      if (key == "log_type") {
        config.logType = (value == "terminal") ? ::Config::LogType::Terminal
                                               : ::Config::LogType::File;
      } else if (key == "log_directory") {
        config.logDirectory = value;
      }
    }
  }

  applyEnvironmentOverrides(config);
  return config;
}

}  // namespace Config
