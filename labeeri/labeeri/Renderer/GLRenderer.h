#pragma once

#include "Renderer/IRenderer.h"

namespace labeeri {

/**
 * @brief OpenGL abstraction of the renderer.
 */
class GLRenderer : public IRenderer {
public:
    /**
     * @brief Sets up some parameters for OpenGL.
     */
    GLRenderer();

    virtual void clear(i32 buffers) override;

    virtual void clearBuffer(i32 buffers, u32 value) override;

    virtual void setClearColor(const vec4& color) override;

    virtual void beginScene(f64 time, const vec3& cameraPosition, const mat4& viewMatrix, const mat4& projectionMatrix,
                            const RenderSceneParameters& parameters = RenderSceneParameters()) override;

    virtual void endOpaque() override;

    virtual void endScene() override;

    virtual void drawToScreen() const override;

    virtual void drawToScreenPostprocessed(bool crosshair = false) override;

    virtual void waitForFrame() override;

    virtual void useShaderProgram(const Ref<ShaderResource>& shaderProgram) override;

    virtual void bindUniform(const char* name, f32 value) override;

    virtual void bindUniform(const char* name, i32 value) override;

    virtual void bindUniform(const char* name, u32 value) override;

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

    virtual MeshResource createMesh(const f32* vertices, u32 vertexCount,
                                    const f32* normals, const f32* tangents,
                                    const std::vector<const f32*>& uvs, const u32* indices, u32 faceCount) const override;

    virtual void deleteMesh(MeshResource& mesh) const override;

    virtual TextureResource createTexture(TextureType type, const ImageResource& image, bool generateMipmap = true,
                                          TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const override;

    virtual TextureResource createCubemap(const std::array<Ref<ImageResource>, 6>& images, TextureFilter filter = TextureFilter::Linear) const override;

    virtual void bindTexture(TextureType type, const TextureResource& texture, u32 slot) const override;

    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                                 uvec2 position, uvec2 size, void* result) const override;

    virtual void deleteTexture(TextureResource& texure) const override;

    virtual Framebuffer createFramebuffer(uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments) const override;

    virtual void bindFramebuffer(const Ref<Framebuffer>& framebuffer) override;

    virtual void deleteFramebuffer(Framebuffer& framebuffer) const override;

    virtual void submitLight(const RendererDirectionalLight& light) override;

    virtual void submitLight(const RendererPointLight& light) override;

    virtual void submitLight(const RendererSpotLight& light) override;

private:
    Ref<MeshResource> m_screenQuad;
    Ref<ShaderResource> m_postprocessShader;
    Ref<ShaderResource> m_skyboxShader;

    Ref<Framebuffer> m_currentFramebuffer;
    Ref<ShaderResource> m_currentShaderProgram;
    Ref<MeshResource> m_currentMesh;
    f64 m_time = 0.0;
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

    /*
     *  @brief Creates the screen quad and loads the skybox and postprocess shaders.
     */
    void initialize();

    MeshResource createScreenQuad() const;

    void bindDirectionalLights();

    void bindPointLights();

    void bindSpotLights();

    void bindFog();

    void drawSkybox();
};

}  // namespace labeeri
