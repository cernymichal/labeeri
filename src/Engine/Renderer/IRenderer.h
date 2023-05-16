#pragma once

#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Renderer/Image.h"
#include "Engine/Renderer/Light.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/RendererParameters.h"
#include "Engine/Renderer/ShaderProgram.h"
#include "Engine/Renderer/Texture.h"

namespace labeeri::Engine {

class Application;

class IRenderer {
public:
    /**
     * @brief TODO
     */
    virtual ~IRenderer() = default;

    /**
     * @brief TODO
     */
    virtual void clear(int buffers) = 0;

    /**
     * @brief TODO
     */
    virtual void clearBuffer(int buffers, uint32_t value) = 0;

    /**
     * @brief TODO
     */
    virtual void setClearColor(const glm::vec4& color) = 0;

    /**
     * @brief TODO
     */
    virtual void beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
                            const RenderSceneParameters& parameters = RenderSceneParameters()) = 0;

    /**
     * @brief TODO
     */
    virtual void endOpaque() = 0;

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
    virtual void drawToScreenPostprocessed() = 0;

    /**
     * @brief TODO
     */
    virtual void waitForFrame() = 0;

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
    virtual void bindUniform(const char* name, int32_t value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, uint32_t value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const glm::mat4& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const glm::vec2& value) = 0;

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
    virtual Texture createTexture(TextureType type, const Image& image, bool generateMipmap = true,
                                  TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const = 0;

    /**
     * @brief TODO
     */
    virtual Texture createCubemap(const std::array<Scoped<Image>, 6>& images, TextureFilter filter = TextureFilter::Linear) const = 0;

    /**
     * @brief TODO
     */
    virtual void bindTexture(TextureType type, const Texture& texture, unsigned slot = 0) const = 0;

    /**
     * @brief TODO
     */
    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                             glm::uvec2 position, glm::uvec2 size, void* result) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteTexture(Texture& texure) const = 0;

    /**
     * @brief TODO
     */
    virtual Framebuffer createFramebuffer(glm::uvec2 size, std::map<FramebufferAttachment, Ref<Texture>>&& attachments) const = 0;

    /**
     * @brief TODO
     */
    virtual void bindFramebuffer(const Ref<Framebuffer>& framebuffer) = 0;

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
