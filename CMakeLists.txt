cmake_minimum_required(VERSION 3.16)
project(HOI4Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Werror)

# Fetch external dependencies
add_subdirectory(external)

# Engine and game
add_subdirectory(engine)
add_subdirectory(game)

# Tools
add_subdirectory(tools)

# Tests
enable_testing()
add_subdirectory(tests)
