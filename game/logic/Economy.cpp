#include "Economy.h"

namespace game::logic {

int Economy::factoriesFromTrade(const Resources& res) {
    int total = res.oil + res.steel + res.chromium;
    return total / 8;
}

} // namespace game::logic
