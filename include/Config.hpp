#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>

namespace Config {

enum class LogType { Terminal, File };

struct Config {
  LogType logType = LogType::File;
  std::string logDirectory = "log/date.log";
};

Config loadConfig(const std::filesystem::path& path);

}  // namespace Config

#endif  // CONFIG_HPP
