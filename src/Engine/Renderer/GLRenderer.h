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

    virtual void setClearColor(const glm::vec4& color) override;

    virtual void beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix,
                            const RenderSceneParameters& parameters = RenderSceneParameters()) override;

    virtual void endOpaque() override;

    virtual void endScene() override;

    virtual void drawToScreen() const override;

    virtual void drawToScreenPostprocessed() override;

    virtual void waitForFrame() override;

    virtual void useShaderProgram(const Ref<ShaderProgram>& shaderProgram) override;

    virtual void bindUniform(const char* name, float value) override;

    virtual void bindUniform(const char* name, int32_t value) override;

    virtual void bindUniform(const char* name, uint32_t value) override;

    virtual void bindUniform(const char* name, const glm::mat4& value) override;

    virtual void bindUniform(const char* name, const glm::vec2& value) override;

    virtual void bindUniform(const char* name, const glm::vec3& value) override;

    virtual void bindPVM(const glm::mat4& modelMatrix) override;

    virtual LAB_GL_INT getUniformLocation(ShaderProgram& shaderProgram, const char* name) override;

    virtual void bindMesh(const Ref<Mesh>& mesh) override;

    virtual void drawMesh() override;

    virtual ShaderProgram createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const override;

    virtual void deleteShaderProgram(ShaderProgram& shaderProgram) const override;

    virtual Mesh createMesh(const float* vertices, uint32_t vertexCount,
                            const float* normals, const float* tangents,
                            const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const override;

    virtual void deleteMesh(Mesh& mesh) const override;

    virtual Texture createTexture(TextureType type, const Image& image, bool generateMipmap = true,
                                  TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const override;

    virtual Texture createCubemap(const std::array<Scoped<Image>, 6>& images, TextureFilter filter = TextureFilter::Linear) const override;

    virtual void bindTexture(TextureType type, const Texture& texture, unsigned slot) const override;

    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                             glm::uvec2 position, glm::uvec2 size, void* result) const override;

    virtual void deleteTexture(Texture& texure) const override;

    virtual Framebuffer createFramebuffer(glm::uvec2 size, std::map<FramebufferAttachment, Ref<Texture>>&& attachments) const override;

    virtual void bindFramebuffer(const Ref<Framebuffer>& framebuffer) override;

    virtual void deleteFramebuffer(Framebuffer& framebuffer) const override;

    virtual void submitLight(const RendererDirectionalLight& light) override;

    virtual void submitLight(const RendererPointLight& light) override;

    virtual void submitLight(const RendererSpotLight& light) override;

    virtual void logError(const char* location) const override;

private:
    Ref<Mesh> m_screenQuad;
    Ref<ShaderProgram> m_postprocessShader;
    Ref<ShaderProgram> m_skyboxShader;

    Ref<Framebuffer> m_currentFramebuffer;
    Ref<ShaderProgram> m_currentShaderProgram;
    Ref<Mesh> m_currentMesh;
    double m_time = 0.0;
    glm::vec3 m_cameraPosition = glm::vec3(0.0f);
    struct Matrices {
        glm::mat4 view = glm::mat4(1.0);
        glm::mat4 viewInverse = glm::mat4(1.0);
        glm::mat4 projection = glm::mat4(1.0);
        glm::mat4 projectionInverse = glm::mat4(1.0);
    } m_matrices;
    RenderSceneParameters m_sceneParameters;

    std::vector<RendererDirectionalLight> m_directionalLights;
    std::vector<RendererPointLight> m_pointLights;
    std::vector<RendererSpotLight> m_spotLights;

    void initialize();

    Mesh createScreenQuad() const;

    void bindDirectionalLights();

    void bindPointLights();

    void bindSpotLights();

    void bindFog();

    void drawSkybox();
};

}  // namespace labeeri::Engine
