#pragma once

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class GLRenderer : public IRenderer {
public:
    /**
     * @brief TODO
     */
    GLRenderer();

    virtual void clear(int buffers) override;

    virtual void clearBuffer(int buffers, uint32_t value) override;

    virtual void setClearColor(const vec4& color) override;

    virtual void beginScene(double time, const vec3& cameraPosition, const mat4& viewMatrix, const mat4& projectionMatrix,
                            const RenderSceneParameters& parameters = RenderSceneParameters()) override;

    virtual void endOpaque() override;

    virtual void endScene() override;

    virtual void drawToScreen() const override;

    virtual void drawToScreenPostprocessed() override;

    virtual void waitForFrame() override;

    virtual void useShaderProgram(const Ref<ShaderResource>& shaderProgram) override;

    virtual void bindUniform(const char* name, float value) override;

    virtual void bindUniform(const char* name, int32_t value) override;

    virtual void bindUniform(const char* name, uint32_t value) override;

    virtual void bindUniform(const char* name, const mat4& value) override;

    virtual void bindUniform(const char* name, const vec2& value) override;

    virtual void bindUniform(const char* name, const uvec2& value) override;

    virtual void bindUniform(const char* name, const vec3& value) override;

    virtual void bindPVM(const mat4& modelMatrix) override;

    virtual LAB_GL_INT getUniformLocation(ShaderResource& shaderProgram, const char* name) override;

    virtual void bindMesh(const Ref<MeshResource>& mesh) override;

    virtual void drawMesh() override;

    virtual ShaderResource createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const override;

    virtual void deleteShaderProgram(ShaderResource& shaderProgram) const override;

    virtual MeshResource createMesh(const float* vertices, uint32_t vertexCount,
                            const float* normals, const float* tangents,
                            const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const override;

    virtual void deleteMesh(MeshResource& mesh) const override;

    virtual TextureResource createTexture(TextureType type, const ImageResource& image, bool generateMipmap = true,
                                  TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const override;

    virtual TextureResource createCubemap(const std::array<Scoped<ImageResource>, 6>& images, TextureFilter filter = TextureFilter::Linear) const override;

    virtual void bindTexture(TextureType type, const TextureResource& texture, unsigned slot) const override;

    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                             uvec2 position, uvec2 size, void* result) const override;

    virtual void deleteTexture(TextureResource& texure) const override;

    virtual Framebuffer createFramebuffer(uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments) const override;

    virtual void bindFramebuffer(const Ref<Framebuffer>& framebuffer) override;

    virtual void deleteFramebuffer(Framebuffer& framebuffer) const override;

    virtual void submitLight(const RendererDirectionalLight& light) override;

    virtual void submitLight(const RendererPointLight& light) override;

    virtual void submitLight(const RendererSpotLight& light) override;

    virtual void logError(const char* location) const override;

private:
    Ref<MeshResource> m_screenQuad;
    Ref<ShaderResource> m_postprocessShader;
    Ref<ShaderResource> m_skyboxShader;

    Ref<Framebuffer> m_currentFramebuffer;
    Ref<ShaderResource> m_currentShaderProgram;
    Ref<MeshResource> m_currentMesh;
    double m_time = 0.0;
    vec3 m_cameraPosition = vec3(0.0f);
    struct Matrices {
        mat4 view = mat4(1.0);
        mat4 viewInverse = mat4(1.0);
        mat4 projection = mat4(1.0);
        mat4 projectionInverse = mat4(1.0);
    } m_matrices;
    RenderSceneParameters m_sceneParameters;

    std::vector<RendererDirectionalLight> m_directionalLights;
    std::vector<RendererPointLight> m_pointLights;
    std::vector<RendererSpotLight> m_spotLights;

    void initialize();

    MeshResource createScreenQuad() const;

    void bindDirectionalLights();

    void bindPointLights();

    void bindSpotLights();

    void bindFog();

    void drawSkybox();
};

}  // namespace labeeri::Engine
