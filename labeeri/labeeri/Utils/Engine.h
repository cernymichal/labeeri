#pragma once

#include "Utils/Math.h"

#ifdef LAB_DEBUG

#define LAB_DEBUG_ONLY(x) x

#else

/**
 * @brief execute only in debug mode
 *
 * @param[in] x expression to execute
 */
#define LAB_DEBUG_ONLY(x)

#endif

#define LAB_BIT(x) (1 << (x))

using LAB_GL_UINT = u32;  // so that we dont have to include GLAD everywhere
using LAB_GL_INT = i32;
using LAB_GL_HANDLE = LAB_GL_UINT;

#define LAB_APP labeeri::Application::Instance()
#define LAB_CURRENT_SCENE LAB_APP.scene()
#define LAB_CURRENT_CAMERA LAB_APP.camera()
#define LAB_IMGUI LAB_APP.imGuiLayer()
#define LAB_WINDOW labeeri::IWindow::Instance()
#define LAB_RENDERER labeeri::IRenderer::Instance()
#define LAB_ECS labeeri::ECS::CURRENT_INSTANCE

namespace labeeri {

// GL 4.6 + GLSL 460
inline constexpr struct GlVersion {
    i32 major = 4;
    i32 minor = 6;
    const char* glsl = "#version 460 core";
} LAB_GL_VERSION;

inline constexpr vec3 VEC_FORWARD = vec3(0.0f, 0.0f, -1.0f);  // Forward is -Z
inline constexpr vec3 VEC_UP = vec3(0.0f, 1.0f, 0.0f);        // Up is +Y
inline constexpr vec3 VEC_RIGHT = vec3(1.0f, 0.0f, 0.0f);     // Right is +X

inline constexpr f32 FIXED_UPDATE_INTERVAL = (1.0f / 50.0f);  // 50 Hz
inline constexpr u32 MAX_ENTITIES = 2048;
inline constexpr u32 MAX_COMPONENTS = 32;

inline constexpr vec3 FALLBACK_COLOR = vec3(0.9, 0.0, 0.9);
inline constexpr u32 MAX_DIRECTIONAL_LIGHTS = 1;
inline constexpr u32 MAX_POINT_LIGHTS = 16;
inline constexpr u32 MAX_SPOT_LIGHTS = 4;

inline constexpr uvec2 INITIAL_WINDOW_SIZE = uvec2(1600, 1200);

inline constexpr auto DEFAULT_SHADER_DIRECTORY = "resources/labeeri/shaders";
inline constexpr auto DEFAULT_MESH_DIRECTORY = "resources/labeeri/models";
inline constexpr auto DEFAULT_TEXTURE_DIRECTORY = "resources/labeeri/textures";

}  // namespace labeeri
