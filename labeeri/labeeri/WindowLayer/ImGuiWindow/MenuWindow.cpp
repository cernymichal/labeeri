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

    f32 frameTime = LAB_APP.getPreviousFrameTime();
    f32 gpuTime = LAB_RENDERER->getPreviousFrameGPUTime();
    f32 cpuTime = frameTime - gpuTime;

    f32 rollingAverageAlpha = frameTime / (1000.f * m_rollingAverageWindow);
    f32 avgFrameTime = m_frameTimeAverage.update(frameTime, rollingAverageAlpha);
    f32 avgFrameCPUTime = m_frameCPUTimeAverage.update(cpuTime, rollingAverageAlpha);
    f32 avgFrameGPUTime = m_frameGPUTimeAverage.update(gpuTime, rollingAverageAlpha);

    ImGui::Text("Average FPS: %.1f", 1000.0f / avgFrameTime);
    ImGui::Text("\tReal: %.3f ms/frame", avgFrameTime);
    ImGui::Text("\tCPU:  %.3f ms/frame", avgFrameCPUTime);
    ImGui::Text("\tGPU:  %.3f ms/frame", avgFrameGPUTime);

    ImGui::Text("%u entities", LAB_ECS ? LAB_ECS->m_entityManager->entityCount() : 0);

    ImGui::End();

    return true;
}

}  // namespace labeeri
