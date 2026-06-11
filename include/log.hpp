#ifndef LOG_HPP
#define LOG_HPP

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace Log {

enum class Level { Debug, Info, Warning, Error };

enum class Destination { Terminal, File };

struct Config {
  Destination destination = Destination::File;
  std::string filePath = "logs/date.log";
};

inline Config& getConfig() {
  static Config config;
  return config;
}

inline std::mutex& getMutex() {
  static std::mutex mtx;
  return mtx;
}

inline std::filesystem::path generateLogFilePath(
    const std::filesystem::path& configuredPath) {
  std::filesystem::path path(configuredPath);
  std::filesystem::path directory = path;
  if (path.has_extension()) {
    directory = path.parent_path();
    if (directory.empty()) directory = ".";
  }

  std::time_t now = std::time(nullptr);
  std::tm localTime;
#ifdef _WIN32
  localtime_s(&localTime, &now);
#else
  localtime_r(&now, &localTime);
#endif

  std::ostringstream filename;
  filename << std::setfill('0') << std::setw(2) << localTime.tm_mday << "-"
           << std::setw(2) << localTime.tm_mon + 1 << "-" << std::setw(2)
           << (localTime.tm_year % 100) << "_" << std::setw(2)
           << localTime.tm_hour << "-" << std::setw(2) << localTime.tm_min
           << "-" << std::setw(2) << localTime.tm_sec << ".log";

  return directory / filename.str();
}

inline void initialize(const Config& config) {
  getConfig() = config;
  auto& currentConfig = getConfig();
  if (getConfig().destination == Destination::File) {
    std::filesystem::path path = generateLogFilePath(currentConfig.filePath);
    currentConfig.filePath = path.string();
    std::filesystem::path parentDir = path.parent_path();

    // Check if the parent path is a valid non-empty directory
    // and ensure it does not already exist before creating it
    if (!parentDir.empty() && parentDir != "." &&
        !std::filesystem::exists(parentDir)) {
      std::filesystem::create_directories(path.parent_path());
    }
  }
}

inline const char* levelToString(Level level) {
  switch (level) {
    case Level::Debug:
      return "debug";
    case Level::Info:
      return "info";
    case Level::Warning:
      return "warning";
    case Level::Error:
      return "error";
  }
  return "unknown";
}

inline std::string threadIdToString() {
  std::ostringstream oss;
  oss << std::this_thread::get_id();
  return oss.str();
}

inline void write(Level level, const std::string& message) {
  std::lock_guard<std::mutex> lock(getMutex());
  if (getConfig().destination == Destination::File) {
    std::ofstream stream(getConfig().filePath, std::ios::app);
    if (stream) {
      stream << "[\"" << levelToString(level) << "\"] "
             << "\"" << threadIdToString() << "\": "
             << "\"" << message << "\"" << std::endl;
      return;
    }
    // Fallback to terminal if file cannot be opened.
    std::cerr << "[\"error\"] "
              << "\"" << threadIdToString() << "\": "
              << "\"Unable to open log file.\"" << std::endl;
  }
  std::cout << "[\"" << levelToString(level) << "\"] "
            << "\"" << threadIdToString() << "\": "
            << "\"" << message << "\"" << std::endl;
}

// Variadic overload for multiple arguments (only when Rest has at least one
// element)
template <typename First, typename... Rest,
          typename = std::enable_if_t<(sizeof...(Rest) > 0)>>
inline void write(Level level, First&& first, Rest&&... rest) {
  std::ostringstream oss;
  oss << std::forward<First>(first);
  ((oss << std::forward<Rest>(rest)), ...);
  write(level, oss.str());
}

inline void debug(const std::string& message) { write(Level::Debug, message); }
inline void info(const std::string& message) { write(Level::Info, message); }
inline void warning(const std::string& message) {
  write(Level::Warning, message);
}
inline void error(const std::string& message) { write(Level::Error, message); }

}  // namespace Log

#define LOG_DEBUG(...) Log::write(Log::Level::Debug, __VA_ARGS__)
#define LOG_INFO(...) Log::write(Log::Level::Info, __VA_ARGS__)
#define LOG_WARNING(...) Log::write(Log::Level::Warning, __VA_ARGS__)
#define LOG_ERROR(...) Log::write(Log::Level::Error, __VA_ARGS__)

#define LOG_DEBUG_GLOBAL(msg)                           \
  static const int LOG_DEBUG_GLOBAL_##__LINE__ = []() { \
    Log::debug(msg);                                    \
    return 0;                                           \
  }();

#endif  // LOG_HPP
