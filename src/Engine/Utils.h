#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "Engine/Log.h"

#define LAB_BIT(x) (1 << (x))

using LAB_GL_UINT = unsigned int;  // so that we dont have to include GLAD everywhere
using LAB_GL_INT = int;
using LAB_GL_HANDLE = LAB_GL_UINT;

#define LAB_APP labeeri::Engine::Application::instance()
#define LAB_CURRENT_SCENE LAB_APP.scene()
#define LAB_CURRENT_CAMERA LAB_APP.camera()
#define LAB_IMGUI LAB_APP.imGuiLayer()
#define LAB_WINDOW labeeri::Engine::IWindow::instance()
#define LAB_RENDERER labeeri::Engine::IRenderer::instance()

namespace labeeri::Engine {

constexpr auto INITIAL_WINDOW_SIZE = glm::uvec2(1600, 1200);

constexpr auto DEFAULT_SHADER_DIRECTORY = "resources/engine/shaders";
constexpr auto DEFAULT_MESH_DIRECTORY = "resources/engine/models";
constexpr auto DEFAULT_TEXTURE_DIRECTORY = "resources/engine/textures";

// GL 4.5 + GLSL 450
constexpr auto GL_VERSION_MAJOR = 4;
constexpr auto GL_VERSION_MINOR = 5;
constexpr auto GLSL_VERSION = "#version 450";

constexpr auto FIXED_UPDATE_INTERVAL = (1.0 / 50.0);  // 50 Hz

constexpr auto FALLBACK_COLOR = glm::vec3(0.9, 0.0, 0.9);

constexpr auto MAX_DIRECTIONAL_LIGHTS = 1;
constexpr auto MAX_POINT_LIGHTS = 16;
constexpr auto MAX_SPOT_LIGHTS = 4;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
std::shared_ptr<T> copyShared(const std::shared_ptr<T>& ptr) {
    return std::make_shared<T>(*ptr);
}

}  // namespace labeeri::Engine
