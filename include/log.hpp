#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace Log {

enum class Level { Debug, Info, Warning, Error };

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

inline std::mutex& getMutex() {
  static std::mutex mtx;
  return mtx;
}

inline void write(Level level, const std::string& message) {
  std::lock_guard<std::mutex> lock(getMutex());
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
