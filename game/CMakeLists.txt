add_subdirectory(data)
add_subdirectory(logic)
add_subdirectory(ai)
add_subdirectory(rules)

add_library(game STATIC)

set(game_public_headers
    logic/Economy.h
    ai/AI.h
    rules/Rules.h
)

target_sources(game
    PRIVATE
        logic/Economy.cpp
        ai/AI.cpp
        rules/Rules.cpp
    PUBLIC
        ${game_public_headers}
)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game PUBLIC engine external::json)

set_target_properties(game PROPERTIES PUBLIC_HEADER "${game_public_headers}")
