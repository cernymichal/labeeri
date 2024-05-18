#pragma once

#include "Engine/Utils/Common.h"
#include "Engine/Utils/Math.h"

#define LAB_BIT(x) (1 << (x))

using LAB_GL_UINT = u32;  // so that we dont have to include GLAD everywhere
using LAB_GL_INT = i32;
using LAB_GL_HANDLE = LAB_GL_UINT;

#define LAB_APP labeeri::Engine::Application::Instance()
#define LAB_CURRENT_SCENE LAB_APP.scene()
#define LAB_CURRENT_CAMERA LAB_APP.camera()
#define LAB_IMGUI LAB_APP.imGuiLayer()
#define LAB_WINDOW labeeri::Engine::IWindow::Instance()
#define LAB_RENDERER labeeri::Engine::IRenderer::Instance()
#define LAB_ECS labeeri::Engine::ECS::CURRENT_INSTANCE

namespace labeeri::Engine {

inline constexpr auto INITIAL_WINDOW_SIZE = uvec2(1600, 1200);

inline constexpr auto DEFAULT_SHADER_DIRECTORY = "resources/engine/shaders";
inline constexpr auto DEFAULT_MESH_DIRECTORY = "resources/engine/models";
inline constexpr auto DEFAULT_TEXTURE_DIRECTORY = "resources/engine/textures";

// GL 4.5 + GLSL 450
inline constexpr struct GlVersion {
    i32 major = 4;
    i32 minor = 5;
    const char* glsl = "#version 450 core";
} GL_VERSION;

inline constexpr auto FIXED_UPDATE_INTERVAL = (1.0 / 50.0);  // 50 Hz

inline constexpr auto LAB_FORWARD = vec3(0.0f, 0.0f, -1.0f);  // Forward is -Z
inline constexpr auto LAB_UP = vec3(0.0f, 1.0f, 0.0f);        // Up is +Y
inline constexpr auto LAB_RIGHT = vec3(1.0f, 0.0f, 0.0f);     // Right is +X

inline constexpr auto FALLBACK_COLOR = vec3(0.9, 0.0, 0.9);

inline constexpr auto MAX_DIRECTIONAL_LIGHTS = 1;
inline constexpr auto MAX_POINT_LIGHTS = 16;
inline constexpr auto MAX_SPOT_LIGHTS = 4;

inline constexpr auto MAX_ENTITIES = 2048;
inline constexpr auto MAX_COMPONENTS = 32;

}  // namespace labeeri::Engine
