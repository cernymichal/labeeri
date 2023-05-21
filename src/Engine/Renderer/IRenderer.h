#pragma once

#include "Engine/Renderer/Framebuffer.h"
#include "Engine/Renderer/ImageResource.h"
#include "Engine/Renderer/Light.h"
#include "Engine/Renderer/MeshResource.h"
#include "Engine/Renderer/RendererParameters.h"
#include "Engine/Renderer/ShaderResource.h"
#include "Engine/Renderer/TextureResource.h"

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
    virtual void setClearColor(const vec4& color) = 0;

    /**
     * @brief TODO
     */
    virtual void beginScene(double time, const vec3& cameraPosition, const mat4& viewMatrix, const mat4& projectionMatrix,
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
    virtual void useShaderProgram(const Ref<ShaderResource>& shaderProgram) = 0;

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
    virtual void bindUniform(const char* name, const mat4& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const vec2& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, const vec3& value) = 0;

    /**
     * @brief TODO
     */
    virtual void bindPVM(const mat4& modelMatrix) = 0;

    /**
     * @brief TODO
     */
    virtual LAB_GL_INT getUniformLocation(ShaderResource& shaderProgram, const char* name) = 0;

    /**
     * @brief TODO
     */
    virtual void bindMesh(const Ref<MeshResource>& mesh) = 0;

    /**
     * @brief TODO
     */
    virtual void drawMesh() = 0;

    /**
     * @brief TODO
     */
    virtual ShaderResource createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteShaderProgram(ShaderResource& shaderProgram) const = 0;

    /**
     * @brief TODO
     */
    virtual MeshResource createMesh(const float* vertices, uint32_t vertexCount,
                                    const float* normals, const float* tangets,
                                    const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteMesh(MeshResource& mesh) const = 0;

    /**
     * @brief TODO
     */
    virtual TextureResource createTexture(TextureType type, const ImageResource& image, bool generateMipmap = true,
                                          TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const = 0;

    /**
     * @brief TODO
     */
    virtual TextureResource createCubemap(const std::array<Scoped<ImageResource>, 6>& images, TextureFilter filter = TextureFilter::Linear) const = 0;

    /**
     * @brief TODO
     */
    virtual void bindTexture(TextureType type, const TextureResource& texture, unsigned slot = 0) const = 0;

    /**
     * @brief TODO
     */
    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                                 uvec2 position, uvec2 size, void* result) const = 0;

    /**
     * @brief TODO
     */
    virtual void deleteTexture(TextureResource& texure) const = 0;

    /**
     * @brief TODO
     */
    virtual Framebuffer createFramebuffer(uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments) const = 0;

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
    static IRenderer* Instance() {
        return s_renderer.get();
    }

private:
    static inline std::unique_ptr<IRenderer> s_renderer;

    friend Application;
};

}  // namespace labeeri::Engine
