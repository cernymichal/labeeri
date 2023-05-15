#pragma once

#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Renderer/Light.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/ShaderProgram.h"
#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

class Application;

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

class IRenderer {
public:
    /**
     * @brief TODO
     */
    virtual ~IRenderer() = default;

    /**
     * @brief TODO
     */
    virtual void setViewportSize(glm::uvec2 size) = 0;

    /**
     * @brief TODO
     */
    virtual void clear(int buffers) = 0;

    /**
     * @brief TODO
     */
    virtual void setClearColor(const glm::vec4& color) = 0;

    /**
     * @brief TODO
     */
    virtual void beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const FogParameters& fog = FogParameters()) = 0;

    /**
     * @brief TODO
     */
    virtual void endScene() = 0;

    /**
     * @brief TODO
     */
    virtual void drawToScreen() const = 0;

    /**
     * @brief TODO
     */
    virtual void drawToScreenPostprocessed(const PostprocessingParameters& parameters = PostprocessingParameters()) = 0;

    /**
     * @brief TODO
     */
    virtual void useShaderProgram(const Ref<ShaderProgram>& shaderProgram) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, float value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, int value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const glm::mat4& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const glm::vec3& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindPVM(const glm::mat4& modelMatrix) = 0;

    /**
     * @brief TODO
     */
    virtual LAB_GL_INT getUniformLocation(ShaderProgram& shaderProgram, const char* name) = 0;

    /**
     * @brief TODO
     */
    virtual void bindMesh(const Ref<Mesh>& mesh) = 0;

    /**
     * @brief TODO
     */
    virtual void drawMesh() = 0;

    /**
     * @brief TODO
     */
    virtual ShaderProgram createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteShaderProgram(ShaderProgram& shaderProgram) const = 0;

    /**
     * @brief TODO
     */
    virtual Mesh createMesh(const float* vertices, uint32_t vertexCount,
                            const float* normals, const float* tangets,
                            const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteMesh(Mesh& mesh) const = 0;

    /**
     * @brief TODO
     */
    virtual Texture createTexture(TextureType type, TextureInternalFormat internalFormat, TextureFormat format, TextureDataType dataType,
                                  glm::uvec2 size, unsigned char* data = nullptr, bool generateMipmap = true,
                                  TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const = 0;

    /**
     * @brief TODO
     */
    virtual void bindTexture(TextureType type, const Texture& texture, unsigned slot = 0) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteTexture(Texture& texure) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteFramebuffer(Framebuffer& framebuffer) const = 0;

    /**
     * @brief TODO
     */
    virtual void submitLight(const RendererDirectionalLight& light) = 0;

    /**
     * @brief TODO
     */
    virtual void submitLight(const RendererPointLight& light) = 0;

    /**
     * @brief TODO
     */
    virtual void submitLight(const RendererSpotLight& light) = 0;

    /**
     * @brief TODO
     */
    virtual void logError(const char* location) const = 0;

    /**
     * @brief TODO
     */
    static IRenderer* instance() {
        return s_renderer.get();
    }

private:
    static std::unique_ptr<IRenderer> s_renderer;

    friend Application;
};

}  // namespace labeeri::Engine
