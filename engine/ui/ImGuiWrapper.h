#pragma once

#include <imgui.h>
#include <string>
#include <expected>

namespace engine::ui {

class ImGuiWrapper {
public:
    std::expected<void, std::string> init();
    void shutdown();
    void newFrame();
    void render();
};

} // namespace engine::ui
