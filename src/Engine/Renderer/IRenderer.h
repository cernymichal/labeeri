#pragma once

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

enum class ShaderType {
    Vertex,
    Fragment
};

enum class TextureType {
    Texture2D,
    Rectangle
};

enum class TextureFormat {
    Red,
    RGB,
    RGBA,
    Depth
};

enum class TextureFilter {
    Nearest,
    Linear
};

enum class TextureWrap {
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
    virtual void beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    /**
     * @brief TODO
     */
    virtual void endScene() = 0;

    /**
     * @brief TODO
     */
    virtual void useShaderProgram(const ShaderProgramRef& shaderProgram) = 0;

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
    virtual void bindMesh(const MeshRef& mesh) = 0;

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
    virtual Mesh createMesh(const float* vertices, uint32_t vertexCount, const float* normals, const std::vector<const float*> UVs, const unsigned int* indices, uint32_t faceCount) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteMesh(Mesh& mesh) const = 0;

    /**
     * @brief TODO
     */
    virtual Texture createTexture(TextureType type, TextureFormat format, unsigned char* data, glm::uvec2 size, bool generateMipmap = true, TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const = 0;

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
    static inline IRenderer* get() {
        return s_renderer.get();
    }

private:
    static std::unique_ptr<IRenderer> s_renderer;

    friend Application;
};

}  // namespace labeeri::Engine
