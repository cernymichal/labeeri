#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "Engine/Log.h"

#define LAB_BIT(x) (1 << (x))

using LAB_GL_UINT = unsigned int;  // so that we dont have to include GLAD everywhere
using LAB_GL_INT = int;
using LAB_GL_HANDLE = LAB_GL_UINT;

#define LAB_APP labeeri::Engine::Application::Instance()
#define LAB_CURRENT_SCENE LAB_APP.scene()
#define LAB_CURRENT_CAMERA LAB_APP.camera()
#define LAB_IMGUI LAB_APP.imGuiLayer()
#define LAB_WINDOW labeeri::Engine::IWindow::Instance()
#define LAB_RENDERER labeeri::Engine::IRenderer::Instance()
#define LAB_ECS labeeri::Engine::ECS::CURRENT_INSTANCE

namespace labeeri::Engine {

inline constexpr auto INITIAL_WINDOW_SIZE = glm::uvec2(1600, 1200);

inline constexpr auto DEFAULT_SHADER_DIRECTORY = "resources/engine/shaders";
inline constexpr auto DEFAULT_MESH_DIRECTORY = "resources/engine/models";
inline constexpr auto DEFAULT_TEXTURE_DIRECTORY = "resources/engine/textures";

// GL 4.5 + GLSL 450
inline constexpr auto GL_VERSION_MAJOR = 4;
inline constexpr auto GL_VERSION_MINOR = 5;
inline constexpr auto GLSL_VERSION = "#version 450";

inline constexpr auto FIXED_UPDATE_INTERVAL = (1.0 / 50.0);  // 50 Hz

inline constexpr auto LAB_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);
inline constexpr auto LAB_UP = glm::vec3(0.0f, 1.0f, 0.0f);
inline constexpr auto LAB_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);

inline constexpr auto FALLBACK_COLOR = glm::vec3(0.9, 0.0, 0.9);

inline constexpr auto MAX_DIRECTIONAL_LIGHTS = 1;
inline constexpr auto MAX_POINT_LIGHTS = 16;
inline constexpr auto MAX_SPOT_LIGHTS = 4;

inline constexpr auto MAX_ENTITIES = 2048;
inline constexpr auto MAX_COMPONENTS = 32;

template <typename T>
inline std::shared_ptr<T> copyShared(const std::shared_ptr<T>& ptr) {
    return std::make_shared<T>(*ptr);
}

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
inline Ref<T> makeRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename S>
inline Ref<T> castRef(const Ref<S>& ptr) {
    return std::dynamic_pointer_cast<T>(ptr);
}

template <typename T>
inline Ref<T> clone(const Ref<T>& ref) {
    return copyShared<T>(ref);
}

template <typename T, typename S>
inline Ref<T> cloneAs(const Ref<S>& ref) {
    return clone(castRef<T>(ref));
}

template <typename T>
using Scoped = std::unique_ptr<T>;

template <typename T, typename... Args>
inline Scoped<T> makeScoped(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<2, T>& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<3, T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const glm::vec<4, T>& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

}  // namespace labeeri::Engine
