#include "Logger.h"

namespace engine::core {

void Logger::log(Level level, const std::string& message) {
    const char* prefix = "INFO";
    if (level == Level::Warning) prefix = "WARN";
    else if (level == Level::Error) prefix = "ERROR";
    std::cout << "[" << prefix << "] " << message << std::endl;
}

} // namespace engine::core
