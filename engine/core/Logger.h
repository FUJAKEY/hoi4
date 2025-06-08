#pragma once

#include <string>
#include <iostream>

namespace engine::core {

class Logger {
public:
    enum class Level { Info, Warning, Error };

    Logger() = default;

    void log(Level level, const std::string& message);
};

} // namespace engine::core
