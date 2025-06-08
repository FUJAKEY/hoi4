#pragma once

#include <expected>
#include <string>
#include <cstdint>

namespace game::logic {

struct Resources {
    int oil{0};
    int steel{0};
    int chromium{0};
};

class Economy {
public:
    static int factoriesFromTrade(const Resources& res);
};

} // namespace game::logic
