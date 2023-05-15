#pragma once

#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

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
	glm::vec3 color = glm::vec3(0.8f);
	float density = 0.01f;
};

struct RenderSceneParameters {
	FogParameters fog;
    PostprocessingParameters postprocessing;
    Ref<Texture> skybox;
};

enum class ShaderType : uint8_t {
    Vertex,
    Fragment,
    Geometry
};

enum class TextureType : uint8_t {
    Texture2D,
    Rectangle
};

enum class TextureInternalFormat : uint8_t {
    Red,
    RGB,
    RGBA,
    SRGB,
    SRGBA,
    RGBAFloat16,
    DepthFloat32
};

enum class TextureFormat : uint8_t {
    Red,
    RGB,
    RGBA,
    Depth
};

enum class TextureDataType : uint8_t {
    UnsignedByte,
    Float16,
    Float32
};

enum class TextureFilter : uint8_t {
    Nearest,
    Linear
};

enum class TextureWrap : uint8_t {
    ClampToEdge,
    Repeat,
    MirroredRepeat,
};

}  // namespace labeeri::Engine
