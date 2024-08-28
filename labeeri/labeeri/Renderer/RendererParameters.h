#pragma once

#include "Renderer/TextureResource.h"

namespace labeeri {

/**
 * @brief Buffer types to be cleared.
 */
enum class ClearBuffer {
    Color = LAB_BIT(0),
    Depth = LAB_BIT(1),
    Stencil = LAB_BIT(2)
};

struct PostprocessingParameters {
    f32 exposure = 1.0f;
    f32 gamma = 2.2f;
};

struct FogParameters {
    vec3 color = vec3(0.8f);
    f32 density = 0.02f;
};

/**
 * @brief Scenes parameters for rendering.
 */
struct RenderSceneParameters {
    FogParameters fog;
    PostprocessingParameters postprocessing;
    Ref<TextureResource> skybox;
};

enum class ShaderType : u8 {
    Vertex,
    Fragment,
    Geometry
};

enum class TextureType : u8 {
    Texture2D,
    Rectangle,
    Cubemap
};

enum class TextureInternalFormat : u8 {
    RGB,
    RGBA,
    SRGB,
    SRGBA,
    RGBFloat16,
    RGBAFloat16,
    RGBFloat32,
    RGBAFloat32,
    RedUInt32,
    DepthFixed24
};

enum class TextureFormat : u8 {
    Red,
    RGB,
    RGBA,
    RedInt,
    Depth
};

enum class TextureDataType : u8 {
    UByte,
    UInt32,
    Float16,
    Float32
};

/**
 * @brief Texture magnification / minification filter.
 */
enum class TextureFilter : u8 {
    Nearest,
    Linear
};

/**
 * @brief Texture edge wrapping mode.
 */
enum class TextureWrap : u8 {
    ClampToEdge,
    Repeat,
    MirroredRepeat,
};

}  // namespace labeeri
