include(FetchContent)

FetchContent_Declare(SDL2
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.26.1.zip
)
FetchContent_Declare(SDL2_image
    URL https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.6.2.zip
)
FetchContent_Declare(SDL2_ttf
    URL https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.20.1.zip
)
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)
FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.10.5
)
FetchContent_Declare(dearimgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.2
)

FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_ttf glm nlohmann_json dearimgui)

# Provide interface libraries
add_library(external_sdl INTERFACE)
add_library(external::sdl ALIAS external_sdl)
target_link_libraries(external_sdl INTERFACE SDL2 SDL2_image SDL2_ttf)

add_library(external_glm INTERFACE)
add_library(external::glm ALIAS external_glm)
target_link_libraries(external_glm INTERFACE glm)

add_library(external_json INTERFACE)
add_library(external::json ALIAS external_json)
target_link_libraries(external_json INTERFACE nlohmann_json::nlohmann_json)

add_library(external_imgui INTERFACE)
add_library(external::imgui ALIAS external_imgui)
target_link_libraries(external_imgui INTERFACE imgui)
