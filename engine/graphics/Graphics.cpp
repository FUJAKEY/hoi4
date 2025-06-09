#include "Graphics.h"

namespace engine::graphics {

std::expected<void, std::string> Graphics::init(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return std::unexpected(SDL_GetError());
    }
    window = SDL_CreateWindow("HOI4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_OPENGL);
    if (!window) return std::unexpected(SDL_GetError());

    glctx = SDL_GL_CreateContext(window);
    if (!glctx) return std::unexpected(SDL_GetError());

    return {};
}

void Graphics::shutdown() {
    if (glctx) {
        SDL_GL_DeleteContext(glctx);
        glctx = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Graphics::clear() {
    SDL_GL_SwapWindow(window); // simple placeholder
}

void Graphics::present() {
    SDL_GL_SwapWindow(window);
}

} // namespace engine::graphics
