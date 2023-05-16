#include "ViewportLayer.h"

#include "Engine/Application.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Window/IWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/EntityWindow.h"

namespace labeeri::Engine {

ViewportLayer::ViewportLayer() {
    LAB_LOGH2("ViewportLayer::ViewportLayer()");

    m_size = LAB_WINDOW->m_frameBufferSize();
    updateViewFramebuffer();
}

void ViewportLayer::onEvent(IEvent& e) {
    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onRender));
    e.dispatch<WindowResizeEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onResize));
    e.dispatch<MouseButtonPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onMouseButtonPress));
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(ViewportLayer::onKeyboardPress));
}

bool ViewportLayer::onRender(const ApplicationRenderEvent& e) {
    if (!LAB_CURRENT_SCENE) return false;

    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(m_size);

    LAB_RENDERER->beginScene(LAB_CURRENT_SCENE->time(), m_camera->transform()->worldPosition(), viewMatrix, projectionMatrix, LAB_CURRENT_SCENE->m_renderParameters);
    LAB_RENDERER->bindFramebuffer(m_viewFramebuffer);
    LAB_RENDERER->clear(static_cast<int>(ClearBuffer::Depth));

    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        if (entity->m_light)
            entity->m_light->submit(*entity->transform());
    }

    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        if (entity->m_model)
            entity->m_model->draw(entity->transform()->modelMatrix());
    }

    LAB_RENDERER->endOpaque();

    LAB_RENDERER->endScene();
    LAB_RENDERER->drawToScreenPostprocessed();
    LAB_LOG_RENDERAPI_ERROR();

    return false;
}

bool ViewportLayer::onResize(const WindowResizeEvent& e) {
    m_size = e.windowSize();
    updateViewFramebuffer();
    m_idFramebuffer = nullptr;

    return false;
}

bool ViewportLayer::onMouseButtonPress(const MouseButtonPressEvent& e) {
    if (e.button() == MouseButton::Left && !(e.mods() & LAB_MOD_CONTROL) && LAB_APP.focus() != ApplicationFocus::Viewport) {
        LAB_APP.focusViewport();
        return true;
    }

    if (e.button() == MouseButton::Left && e.mods() & LAB_MOD_CONTROL && LAB_APP.focus() != ApplicationFocus::Viewport) {
        clickOnObject(e.position());
        return true;
    }

    return false;
}

bool ViewportLayer::onKeyboardPress(const KeyboardPressEvent& e) {
    if (e.key() == KeyboardKey::Escape && LAB_APP.focus() == ApplicationFocus::Viewport) {
        LAB_APP.focusUI();
        return true;
    }

    if (e.key() == KeyboardKey::F5) {
        LAB_WINDOW->setFullscreen(!LAB_WINDOW->fullscreen());
        return true;
    }

    return false;
}

void ViewportLayer::updateViewFramebuffer() {
    auto colorBuffer = makeRef<Texture>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    Image(m_size, nullptr, TextureDataType::Float16, TextureFormat::RGBA, TextureInternalFormat::RGBAFloat16), false,
                                    TextureFilter::Linear, TextureWrap::ClampToEdge));

    auto depthBuffer = makeRef<Texture>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    Image(m_size, nullptr, TextureDataType::Float32, TextureFormat::Depth, TextureInternalFormat::DepthFloat32), false,
                                    TextureFilter::Linear, TextureWrap::ClampToEdge));

    m_viewFramebuffer = makeRef<Framebuffer>(
        LAB_RENDERER->createFramebuffer(
            m_size, {{FramebufferAttachment::Color, colorBuffer}, {FramebufferAttachment::Depth, depthBuffer}}));
}

void ViewportLayer::updateIdFramebuffer() {
    auto idBuffer = makeRef<Texture>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    Image(m_size, nullptr, TextureDataType::UInt32, TextureFormat::RedInt, TextureInternalFormat::RedUInt32), false,
                                    TextureFilter::Nearest, TextureWrap::ClampToEdge));

    // Depth buffer is shared with view framebuffer
    m_idFramebuffer = makeRef<Framebuffer>(
        LAB_RENDERER->createFramebuffer(
            m_size, {{FramebufferAttachment::Color, idBuffer}, {FramebufferAttachment::Depth, m_viewFramebuffer->m_attachments.at(FramebufferAttachment::Depth)}}));
}

void ViewportLayer::clickOnObject(const glm::uvec2& mousePosition) {
    if (!LAB_CURRENT_SCENE)
        return;

    if (!m_idFramebuffer)
        updateIdFramebuffer();

    auto viewMatrix = m_camera->viewMatrix();
    auto projectionMatrix = m_camera->projectionMatrix(m_size);

    LAB_RENDERER->beginScene(LAB_CURRENT_SCENE->time(), m_camera->transform()->worldPosition(), viewMatrix, projectionMatrix, LAB_CURRENT_SCENE->m_renderParameters);
    LAB_RENDERER->bindFramebuffer(m_idFramebuffer);
    LAB_RENDERER->clear(static_cast<int>(ClearBuffer::Depth));
    LAB_RENDERER->clearBuffer(static_cast<int>(ClearBuffer::Color), 0);
    LAB_RENDERER->useShaderProgram(Resources<ShaderProgram>::get("id"));

    uint32_t id = 0;
    for (auto& entity : LAB_CURRENT_SCENE->entities()) {
        id++;
        if (!entity->m_model)
            continue;

        LAB_RENDERER->bindMesh(entity->m_model->m_mesh);
        LAB_RENDERER->bindPVM(entity->transform()->modelMatrix());
        LAB_RENDERER->bindUniform("u_id", id);
        LAB_RENDERER->drawMesh();
    }

    LAB_RENDERER->endScene();
    LAB_RENDERER->waitForFrame();
    LAB_LOG_RENDERAPI_ERROR();

    LAB_RENDERER->bindFramebuffer(m_idFramebuffer);
    LAB_RENDERER->readFramebuffer(TextureFormat::RedInt, TextureDataType::UInt32, glm::uvec2(mousePosition.x, m_size.y - mousePosition.y - 1), glm::uvec2(1), &id);
    LAB_LOG_RENDERAPI_ERROR();
    id--;

    LAB_IMGUI->addWindow(std::make_unique<EntityWindow>(LAB_CURRENT_SCENE->entities()[id], id));

    LAB_LOG("Clicked on object with id " << id);
}

}  // namespace labeeri::Engine
