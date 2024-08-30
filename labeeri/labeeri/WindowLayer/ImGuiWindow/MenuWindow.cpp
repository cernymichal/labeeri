#include "MenuWindow.h"

#include "Application.h"
#include "Renderer/IRenderer.h"
#include "Utils/imgui.h"
#include "Window/IWindow.h"
#include "WindowLayer/ImGuiWindow/HelpWindow.h"
#include "WindowLayer/ImGuiWindow/LogWindow.h"

namespace labeeri {

static void postprocessingSection() {
    if (!ImGui::CollapsingHeader("Postprocessing"))
        return;

    if (!LAB_CURRENT_SCENE)
        return;

    auto& parameters = LAB_CURRENT_SCENE->m_renderParameters;

    ImGui::InputFloat("Exposure", &parameters.postprocessing.exposure);
    // ImGui::InputFloat("Contrast", &parameters.postprocessing.contrast);
    // ImGui::InputFloat("Brightness", &parameters.postprocessing.brightness);
    // ImGui::InputFloat("Saturation", &parameters.postprocessing.saturation);
    ImGui::InputFloat("Gamma", &parameters.postprocessing.gamma);
}

static void fogSection() {
    if (!ImGui::CollapsingHeader("Fog"))
        return;

    if (!LAB_CURRENT_SCENE)
        return;

    auto& parameters = LAB_CURRENT_SCENE->m_renderParameters;

    ImGui::ColorEdit3("Color", glm::value_ptr(parameters.fog.color));
    ImGui::SliderFloat("Density", &parameters.fog.density, 0, 1);
}

MenuWindow::MenuWindow() {
    m_VSync = LAB_WINDOW->VSync();
}

bool MenuWindow::draw() {
    ImGui::SetNextWindowSize(vec2(400, 200) * LAB_WINDOW->contentScale(), ImGuiCond_FirstUseEver);

    ImGui::Begin(m_name.c_str());

    if (ImGui::Button("Open Help"))
        LAB_IMGUI->addWindow(std::make_unique<HelpWindow>());

    ImGui::SameLine();

    if (ImGui::Button("Open Log"))
        LAB_IMGUI->addWindow(std::make_unique<LogWindow>());

    ImGui::Separator();

    postprocessingSection();
    fogSection();

    ImGui::Separator();

    bool vSyncChanged = ImGui::Checkbox("VSync", &m_VSync);
    if (vSyncChanged)
        LAB_WINDOW->setVSync(m_VSync);

    f32 framerate = ImGui::GetIO().Framerate;
    f32 gpuTime = LAB_RENDERER->getPreviousFrameGPUTime();
    f32 cpuTime = LAB_APP.getPreviousFrameTime() - gpuTime;
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);
    ImGui::Text("CPU time %.3f ms/frame", cpuTime);
    ImGui::Text("GPU time %.3f ms/frame", gpuTime);
    ImGui::Text("%u entities", LAB_ECS ? LAB_ECS->m_entityManager->entityCount() : 0);

    ImGui::End();

    return true;
}

}  // namespace labeeri
