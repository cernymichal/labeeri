#include "ViewportLayer.h"

#include "Engine/Application.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Scene/Components/Camera.h"
#include "Engine/Scene/Components/Transform.h"
#include "Engine/Window/IWindow.h"
#include "Engine/WindowLayer/ImGuiWindow/EntityWindow.h"

namespace labeeri::Engine {

ViewportLayer::ViewportLayer() {
    LAB_LOGH2("ViewportLayer::ViewportLayer()");

    m_size = LAB_WINDOW->frameSize();
    updateViewFramebuffer();
}

void ViewportLayer::onEvent(IEvent& e) {
    e.dispatch<ApplicationRenderEvent>(LAB_BIND_EVENT_FUNC(onRender));
    e.dispatch<WindowResizeEvent>(LAB_BIND_EVENT_FUNC(onResize));
    e.dispatch<MouseButtonPressEvent>(LAB_BIND_EVENT_FUNC(onMouseButtonPress));
    e.dispatch<KeyboardPressEvent>(LAB_BIND_EVENT_FUNC(onKeyboardPress));
}

bool ViewportLayer::onRender(const ApplicationRenderEvent& e) {
    if (!LAB_CURRENT_SCENE) return false;

    auto camera = m_camera.getComponent<Camera>();
    auto cameraPosition = m_camera.getComponent<Transform>();

    auto viewMatrix = camera->viewMatrix(*cameraPosition);
    auto projectionMatrix = camera->projectionMatrix(m_size);

    LAB_RENDERER->beginScene(LAB_CURRENT_SCENE->time(), cameraPosition->worldPosition(), viewMatrix, projectionMatrix, LAB_CURRENT_SCENE->m_renderParameters);
    LAB_RENDERER->bindFramebuffer(m_viewFramebuffer);
    LAB_RENDERER->clear(static_cast<i32>(ClearBuffer::Depth));

    LAB_CURRENT_SCENE->m_systems.light->bindLights();

    LAB_CURRENT_SCENE->m_systems.render->drawOpaque();

    LAB_RENDERER->endOpaque();

    LAB_CURRENT_SCENE->m_systems.render->drawTransparent();

    LAB_RENDERER->endScene();
    LAB_RENDERER->drawToScreenPostprocessed(camera->m_crosshair);
    LAB_LOG_RENDERAPI_ERROR();

    return false;
}

bool ViewportLayer::onResize(const WindowResizeEvent& e) {
    m_size = e.m_windowSize;
    updateViewFramebuffer();
    m_idFramebuffer = nullptr;

    return false;
}

bool ViewportLayer::onMouseButtonPress(const MouseButtonPressEvent& e) {
    if (e.m_button == MouseButton::Left && !(e.m_mods & LAB_MOD_CONTROL) && LAB_APP.focus() != ApplicationFocus::Viewport) {
        LAB_APP.focusViewport();
        return true;
    }

    if (e.m_button == MouseButton::Left) {
        if (e.m_mods & LAB_MOD_CONTROL && LAB_APP.focus() != ApplicationFocus::Viewport) {
            auto event = EntityClickEvent(clickObject(e.m_position));
            LAB_APP.emitEvent(event);
            return true;
        }
        else if (LAB_APP.focus() == ApplicationFocus::Viewport) {
            auto event = EntityClickEvent(clickObject(vec2(m_size.x / 2, m_size.y / 2)));
            LAB_APP.emitEvent(event);
            return true;
        }
    }

    return false;
}

bool ViewportLayer::onKeyboardPress(const KeyboardPressEvent& e) {
    if (e.m_key == KeyboardKey::Escape && LAB_APP.focus() == ApplicationFocus::Viewport) {
        LAB_APP.focusUI();
        return true;
    }

    if (e.m_key == KeyboardKey::F5) {
        LAB_WINDOW->setFullscreen(!LAB_WINDOW->fullscreen());
        return true;
    }

    return false;
}

void ViewportLayer::updateViewFramebuffer() {
    auto colorBuffer = makeRef<TextureResource>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    ImageResource(m_size, nullptr, TextureDataType::Float16, TextureFormat::RGBA, TextureInternalFormat::RGBAFloat16), false,
                                    TextureFilter::Linear, TextureWrap::ClampToEdge));

    auto depthBuffer = makeRef<TextureResource>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    ImageResource(m_size, nullptr, TextureDataType::Float32, TextureFormat::Depth, TextureInternalFormat::DepthFixed24), false,
                                    TextureFilter::Linear, TextureWrap::ClampToEdge));

    m_viewFramebuffer = makeRef<Framebuffer>(
        LAB_RENDERER->createFramebuffer(
            m_size, {{FramebufferAttachment::Color, colorBuffer}, {FramebufferAttachment::Depth, depthBuffer}}));
}

void ViewportLayer::updateIdFramebuffer() {
    auto idBuffer = makeRef<TextureResource>(
        LAB_RENDERER->createTexture(TextureType::Texture2D,
                                    ImageResource(m_size, nullptr, TextureDataType::UInt32, TextureFormat::RedInt, TextureInternalFormat::RedUInt32), false,
                                    TextureFilter::Nearest, TextureWrap::ClampToEdge));

    // Depth buffer is shared with view framebuffer
    m_idFramebuffer = makeRef<Framebuffer>(
        LAB_RENDERER->createFramebuffer(
            m_size, {{FramebufferAttachment::Color, idBuffer}, {FramebufferAttachment::Depth, m_viewFramebuffer->m_attachments.at(FramebufferAttachment::Depth)}}));
}

EntityId ViewportLayer::clickObject(const uvec2& mousePosition) {
    if (!LAB_CURRENT_SCENE)
        return NULL_ENTITY;

    if (!m_idFramebuffer)
        updateIdFramebuffer();

    auto camera = m_camera.getComponent<Camera>();
    auto cameraPosition = m_camera.getComponent<Transform>();

    auto viewMatrix = camera->viewMatrix(*cameraPosition);
    auto projectionMatrix = camera->projectionMatrix(m_size);

    LAB_RENDERER->beginScene(LAB_CURRENT_SCENE->time(), cameraPosition->worldPosition(), viewMatrix, projectionMatrix, LAB_CURRENT_SCENE->m_renderParameters);
    LAB_RENDERER->bindFramebuffer(m_idFramebuffer);
    LAB_RENDERER->clear(static_cast<i32>(ClearBuffer::Depth));
    LAB_RENDERER->clearBuffer(static_cast<i32>(ClearBuffer::Color), NULL_ENTITY);

    LAB_CURRENT_SCENE->m_systems.render->drawIds();

    LAB_RENDERER->endScene();
    LAB_RENDERER->waitForFrame();
    LAB_LOG_RENDERAPI_ERROR();

    LAB_RENDERER->bindFramebuffer(m_idFramebuffer);

    EntityId id = NULL_ENTITY;
    LAB_RENDERER->readFramebuffer(TextureFormat::RedInt, TextureDataType::UInt32, uvec2(mousePosition.x, m_size.y - mousePosition.y - 1), uvec2(1), &id);

    LAB_LOG_RENDERAPI_ERROR();

    LAB_LOG("Clicked on object with id " << id);

    return id;
}

}  // namespace labeeri::Engine
