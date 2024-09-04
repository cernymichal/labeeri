#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Renderer/GLRenderer.h"
#include "Resources/Load.h"
#include "Resources/Resources.h"
#include "Window/GLFWWindow.h"
#include "WindowLayer/ImGuiLayer.h"
#include "WindowLayer/SceneLayer.h"
#include "WindowLayer/ViewportLayer.h"

namespace labeeri {

Application::Application() {
    LAB_LOGH2("Application::Application()");

#ifdef _DEBUG
    LAB_LOG("DEBUG build");
#else
    LAB_LOG("RELEASE build");
#endif

#ifdef LAB_DEBUG
    LAB_LOG("LAB_DEBUG enabled");
#else
    LAB_LOG("LAB_DEBUG disabled");
#endif

    IWindow::s_window = std::make_unique<GLFWWindow>();
    IRenderer::s_renderer = std::make_unique<GLRenderer>();
}

Application::~Application() {
    LAB_LOGH2("Application::~Application()");

    LAB_APP.setScene(nullptr);
    m_layers.clear();

    IWindow::s_window = nullptr;
}

void Application::initialize() {
    LAB_LOGH1("Application::initialize()");

    m_layers.push_back(std::make_unique<ImGuiLayer>());
    m_imGuiLayer = dynamic_cast<ImGuiLayer*>(m_layers.back().get());
    m_layers.push_back(std::make_unique<ViewportLayer>());
    m_viewportLayer = dynamic_cast<ViewportLayer*>(m_layers.back().get());
    m_layers.push_back(std::make_unique<SceneLayer>());
    m_sceneLayer = dynamic_cast<SceneLayer*>(m_layers.back().get());
}

void Application::focusUI() {
    if (closed())
        return;

    m_focus = ApplicationFocus::UI;
    LAB_WINDOW->setCursorMode(CursorMode::Normal);
}

void Application::focusViewport() {
    if (closed())
        return;

    m_focus = ApplicationFocus::Viewport;
    LAB_WINDOW->setCursorMode(CursorMode::Disabled);
}

void Application::emitEvent(IEvent& e) const {
    for (auto& layer : m_layers) {
        layer->onEvent(e);

        if (e.m_handled)
            break;
    }
}

void Application::emitEvent(ApplicationRenderEvent& e) {
    for (auto& layer : std::ranges::views::reverse(m_layers)) {
        if (layer->enabled())
            layer->onEvent(e);
    }

    LAB_WINDOW->swapBuffers();
}

void Application::run() {
    LAB_LOGH1("Application::run()");

    f64 previousUpdateTime = LAB_WINDOW->currentTime();
    f64 fixedUpdateTimeAccumulator = 0;
    while (!LAB_WINDOW->shouldClose()) {
        auto frameStartTime = std::chrono::high_resolution_clock::now();

        LAB_WINDOW->pollEvents();

        f64 currentTime = LAB_WINDOW->currentTime();
        f64 deltaTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;

        if (LAB_WINDOW->minimized())
            continue;

        fixedUpdateTimeAccumulator += deltaTime;

        // emit fixed updates
        while (fixedUpdateTimeAccumulator >= FIXED_UPDATE_INTERVAL) {
            FixedUpdateEvent fixedUpdateEvent;
            emitEvent(fixedUpdateEvent);

            fixedUpdateTimeAccumulator -= FIXED_UPDATE_INTERVAL;
        }

        // emit update
        UpdateEvent updateEvent(deltaTime);
        emitEvent(updateEvent);

        // emit render
        ApplicationRenderEvent renderEvent;
        emitEvent(renderEvent);

        auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_previousFrameTime = std::chrono::duration_cast<std::chrono::microseconds>(frameEndTime - frameStartTime).count() / 1000.0f;
    }

    m_closed = true;
}

}  // namespace labeeri
