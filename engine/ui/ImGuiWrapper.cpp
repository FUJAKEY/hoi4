#include "ImGuiWrapper.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace engine::ui {

std::expected<void, std::string> ImGuiWrapper::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    return {};
}

void ImGuiWrapper::shutdown() {
    ImGui::DestroyContext();
}

void ImGuiWrapper::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void ImGuiWrapper::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace engine::ui
