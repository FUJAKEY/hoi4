#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <expected>

namespace engine::graphics {

class Graphics {
public:
    std::expected<void, std::string> init(int width, int height);
    void shutdown();
    void clear();
    void present();

private:
    SDL_Window* window{nullptr};
    SDL_GLContext glctx{nullptr};
};

} // namespace engine::graphics
