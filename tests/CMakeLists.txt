FetchContent_Declare(doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(unit-tests test_economy.cpp)
target_link_libraries(unit-tests PRIVATE game doctest::doctest)
add_test(NAME unit-tests COMMAND unit-tests)
