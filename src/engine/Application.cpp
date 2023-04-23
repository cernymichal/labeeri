#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "imgui_windows/LogWindow.h"
#include "imgui_windows/MenuWindow.h"
#include "resources/resources.h"
#include "scene/Entity.h"

namespace labeeri::engine {

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

static void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Application& Application::get() {
    static Application instance;
    return instance;
}

Application::Application() {
    LAB_LOGH2("Application::Application()");

    setupGLFW();
    setupGL();
    setupImGui();

    m_viewport = std::make_unique<Viewport>();

    m_imguiWindows.push_back(std::make_unique<MenuWindow>());
    m_imguiWindows.push_back(std::make_unique<LogWindow>());
}

Application::~Application() {
    LAB_LOGH2("Application::~Application()");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    LAB_LOG_OGL_ERROR();

    glfwDestroyWindow(m_window);
    glfwTerminate();
    
    LAB_DEBUG_ONLY(std::cout << LAB_LOGSTREAM_STR << std::endl);
}

std::shared_ptr<Camera>& Application::camera() const {
    return m_viewport->m_camera;
}

GLFWwindow* Application::window() const {
    return m_window;
}

std::pair<int, int> Application::frameBufferSize() const {
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return {width, height};
}

void Application::setVSync(bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
}

bool Application::closed() const {
    return m_closed;
}

void Application::setupGLFW() {
    LAB_LOGH2("Application::setupGLFW()");

    glfwSetErrorCallback(glfwErrorCallback);

    // Initialize the library
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    // GL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);         // 3.0+ only

    // Create window with graphics context
    m_window = glfwCreateWindow(1600, 1200, "labeeri", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("glfwCreateWindow failed");
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, glfwFramebufferSizeCallback);
    glfwSetKeyCallback(m_window, glfwKeyboardCallback);
    glfwSetCursorPosCallback(m_window, glfwCursorPosCallback);
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
    glfwSetScrollCallback(m_window, glfwScrollCallback);
}

void Application::setupGL() {
    LAB_LOGH2("Application::setupGL()");

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    LAB_LOG("Renderer: " << glGetString(GL_RENDERER));
    LAB_LOG("OpenGL version: " << glGetString(GL_VERSION));
}

void Application::setupImGui() {
    LAB_LOGH2("Application::setupImGui()");

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
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
}

void Application::run() {
    LAB_LOGH2("Application::run()");

    double previousUpdateTime = glfwGetTime();
    while (!glfwWindowShouldClose(m_window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;

        if (m_scene)
            m_scene->update(deltaTime);
        render();
    }

    m_closed = true;
}

void Application::render() {
    m_viewport->render();

    {
        ImGuiFrame frame;
        for (auto& window : m_imguiWindows)
            window->render();
    }

    glfwSwapBuffers(m_window);
}

void Application::glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    LAB_APP.m_viewport->resize(width, height);
    LAB_APP.render();
}

void Application::glfwKeyboardCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    if (ImGui::GetIO().WantCaptureKeyboard && static_cast<KeyAction>(action) != KeyAction::Release)
        return;

    for (auto& entity : LAB_APP.m_scene->entities()) {
        if (entity->m_enabled && entity->m_input && entity->m_input->m_onKeyboard)
            entity->m_input->m_onKeyboard(*entity, static_cast<Keyboard>(key), scanCode, static_cast<KeyAction>(action), mods);
    }
}

void Application::glfwCursorPosCallback(GLFWwindow* window, double x, double y) {
    glm::dvec2 newPosition(x, y);
    glm::dvec2 delta = newPosition - LAB_APP.m_mousePosition;
    LAB_APP.m_mousePosition = newPosition;

    for (auto& entity : LAB_APP.m_scene->entities()) {
        if (entity->m_enabled && entity->m_input && entity->m_input->m_onMouseMove)
            entity->m_input->m_onMouseMove(*entity, newPosition, delta);
    }
}

void Application::glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (ImGui::GetIO().WantCaptureMouse && static_cast<KeyAction>(action) != KeyAction::Release)
        return;

    for (auto& entity : LAB_APP.m_scene->entities()) {
        if (entity->m_enabled && entity->m_input && entity->m_input->m_onMouseButton)
            entity->m_input->m_onMouseButton(*entity, static_cast<MouseButton>(button), static_cast<KeyAction>(action), mods);
    }
}

void Application::glfwScrollCallback(GLFWwindow* window, double deltaX, double deltaY) {
    if (ImGui::GetIO().WantCaptureMouse)
        return;

    for (auto& entity : LAB_APP.m_scene->entities()) {
        if (entity->m_enabled && entity->m_input && entity->m_input->m_onMouseScroll)
            entity->m_input->m_onMouseScroll(*entity, deltaY);
    }
}

}  // namespace labeeri::engine
