#pragma once

#include "Engine/Renderer/TextureResource.h"

namespace labeeri::Engine {

/**
 * @brief Buffer types to be cleared.
 */
enum class ClearBuffer {
    Color = LAB_BIT(0),
    Depth = LAB_BIT(1),
    Stencil = LAB_BIT(2)
};

struct PostprocessingParameters {
    float exposure = 1.0f;
    float gamma = 2.2f;
};

struct FogParameters {
    vec3 color = vec3(0.8f);
    float density = 0.02f;
};

/**
 * @brief Scenes parameters for rendering.
 */
struct RenderSceneParameters {
    FogParameters fog;
    PostprocessingParameters postprocessing;
    Ref<TextureResource> skybox;
};

enum class ShaderType : uint8_t {
    Vertex,
    Fragment,
    Geometry
};

enum class TextureType : uint8_t {
    Texture2D,
    Rectangle,
    Cubemap
};

enum class TextureInternalFormat : uint8_t {
    RGB,
    RGBA,
    SRGB,
    SRGBA,
    RGBFloat16,
    RGBAFloat16,
    RGBFloat32,
    RGBAFloat32,
    RedUInt32,
    DepthFloat32
};

enum class TextureFormat : uint8_t {
    Red,
    RGB,
    RGBA,
    RedInt,
    Depth
};

enum class TextureDataType : uint8_t {
    UByte,
    UInt32,
    Float16,
    Float32
};

/**
 * @brief Texture magnification / minification filter.
 */
enum class TextureFilter : uint8_t {
    Nearest,
    Linear
};

/**
 * @brief Texture edge wrapping mode.
 */
enum class TextureWrap : uint8_t {
    ClampToEdge,
    Repeat,
    MirroredRepeat,
};

}  // namespace labeeri::Engine
