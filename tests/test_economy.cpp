#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "game/logic/Economy.h"

TEST_CASE("trade formula") {
    using game::logic::Economy;
    using game::logic::Resources;
    CHECK(Economy::factoriesFromTrade(Resources{8,0,0}) == 1);
    CHECK(Economy::factoriesFromTrade(Resources{4,4,0}) == 1);
    CHECK(Economy::factoriesFromTrade(Resources{0,0,0}) == 0);
}
