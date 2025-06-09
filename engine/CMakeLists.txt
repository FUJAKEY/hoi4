add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(ui)

add_library(engine STATIC)

# Public headers
set(engine_public_headers
    core/Logger.h
    core/ECS.h
    core/EventBus.h
    graphics/Graphics.h
    ui/ImGuiWrapper.h
)

target_sources(engine
    PRIVATE
        core/Logger.cpp
        core/EventBus.cpp
        graphics/Graphics.cpp
        ui/ImGuiWrapper.cpp
    PUBLIC
        ${engine_public_headers}
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(engine
    PUBLIC
        external::sdl
        external::glm
        external::imgui
)

set_target_properties(engine PROPERTIES PUBLIC_HEADER "${engine_public_headers}")
