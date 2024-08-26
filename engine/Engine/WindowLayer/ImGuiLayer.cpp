#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Engine/Application.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Window/GLFWWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/EntityWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/MenuWindow.h"

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
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            LAB_WINDOW->makeCurrent();
        }
    }
};

ImGuiLayer::ImGuiLayer() {
    LAB_LOGH2("ImGuiLayer::ImGuiLayer()");

    m_enabled = false;
    LAB_DEBUG_ONLY(m_enabled = true);

    setupImGui();

    m_windows.emplace_back(std::make_unique<MenuWindow>());
}

ImGuiLayer::~ImGuiLayer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

IImGuiWindow* ImGuiLayer::addWindow(std::unique_ptr<IImGuiWindow>&& window) {
    auto windowFound = std::ranges::find_if(m_windows, [&](const auto& other) { return *window == *other; });
    if (windowFound != m_windows.end())
        return windowFound->get();

    return m_windows.emplace_back(std::move(window)).get();
}

void ImGuiLayer::setupImGui() {
    LAB_LOGH3("ImGuiLayer::setupImGui()");

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
    io.FontGlobalScale = LAB_WINDOW->contentScale().y;
    style.ScaleAllSizes(LAB_WINDOW->contentScale().y);

    // Setup Platform/Renderer backends
    const GLFWWindow* window = dynamic_cast<GLFWWindow*>(LAB_WINDOW);
    assert(window != nullptr && "ImGuiLayer::setupImGui() - window is not a GLFWWindow.");

    ImGui_ImplGlfw_InitForOpenGL(window->windowObject(), true);
    ImGui_ImplOpenGL3_Init(LAB_GL_VERSION.glsl);
}

void ImGuiLayer::onEvent(IEvent& e) {
    if ((e.isInCategory(EventCategory::Keyboard) && ImGui::GetIO().WantCaptureKeyboard) || (e.isInCategory(EventCategory::Mouse) && ImGui::GetIO().WantCaptureMouse)) {
        e.m_handled = true;
        return;
    }

    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(onRender));
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(onKeyboardPress));
    e.dispatch<EntityClickEvent>(LAB_BIND_EVENT_FUNC(onEntityClick));
}

bool ImGuiLayer::onRender(const ApplicationRenderEvent& e) {
    ImGuiFrame frame;

    for (size_t i = 0; i < m_windows.size(); ++i) {
        if (!m_windows[i]->draw()) {
            m_windows.erase(m_windows.begin() + i);
            --i;
        }
    }

    return false;
}

bool ImGuiLayer::onKeyboardPress(const KeyboardPressEvent& e) {
    if (e.m_key == KeyboardKey::F3) {
        m_enabled = !m_enabled;
        return true;
    }

    return false;
}

bool ImGuiLayer::onEntityClick(const EntityClickEvent& e) {
    if (!e.m_entity || LAB_APP.focus() != ApplicationFocus::UI)
        return false;

    addWindow(std::make_unique<EntityWindow>(e.m_entity));
    return true;
}

}  // namespace labeeri::Engine
