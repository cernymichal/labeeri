#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Engine/Application.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/WindowLayer/ImGuiWindow/LogWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/MenuWindow.h"
#include "GLFW/glfw3.h"

namespace labeeri::Engine {

struct ImGuiFrame {
    ImGuiFrame() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
    }

    ~ImGuiFrame() {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
};

ImGuiLayer::ImGuiLayer() {
    LAB_LOGH2("ImGuiLayer::ImGuiLayer()");

    setupImGui();

    m_windows.push_back(std::make_unique<MenuWindow>());
    m_windows.push_back(std::make_unique<LogWindow>());
}

ImGuiLayer::~ImGuiLayer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::setupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(LAB_APP.window(), true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
}

void ImGuiLayer::onEvent(Event& e) {
    if ((e.isInCategory(EventCategory::Keyboard) && ImGui::GetIO().WantCaptureKeyboard) || (e.isInCategory(EventCategory::Mouse) && ImGui::GetIO().WantCaptureMouse)) {
        e.m_handled = true;
        return;
    }

    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(ImGuiLayer::onRender));
}

bool ImGuiLayer::onRender(const Event& e) {
    ImGuiFrame frame;
    for (auto& window : m_windows)
        window->draw();

    return false;
}

}  // namespace labeeri::Engine
