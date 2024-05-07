#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Renderer/GLRenderer.h"
#include "Engine/Window/GLFWWindow.h"
#include "Engine/WindowLayer/ImGuiLayer.h"
#include "Engine/WindowLayer/SceneLayer.h"
#include "Engine/WindowLayer/ViewportLayer.h"

namespace labeeri::Engine {

Application::Application() {
    LAB_LOGH2("Application::Application()");

    IWindow::s_window = std::make_unique<GLFWWindow>();
    IRenderer::s_renderer = std::make_unique<GLRenderer>();
}

Application::~Application() {
    LAB_LOGH2("Application::~Application()");

    LAB_APP.setScene(nullptr);
    m_layers.clear();

    IWindow::s_window = nullptr;

    LAB_LOG_RENDERAPI_ERROR();
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
    }

    m_closed = true;
}

}  // namespace labeeri::Engine
