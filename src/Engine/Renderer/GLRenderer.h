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

    virtual void setViewportSize(glm::uvec2 size) override;

    virtual void clear(int buffers) override;

    virtual void setClearColor(const glm::vec4& color) override;

    virtual void beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    virtual void endScene() override;

    virtual void useShaderProgram(const Ref<ShaderProgram>& shaderProgram) override;

    virtual void bindUniform(const char* name, float value) override;

    virtual void bindUniform(const char* name, int value) override;

    virtual void bindUniform(const char* name, const glm::mat4& value) override;

    virtual void bindUniform(const char* name, const glm::vec3& value) override;

    virtual void bindPVM(const glm::mat4& modelMatrix) override;

    virtual LAB_GL_INT getUniformLocation(ShaderProgram& shaderProgram, const char* name) override;

    virtual void bindMesh(const Ref<Mesh>& mesh) override;

    virtual void drawMesh() override;

    virtual ShaderProgram createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const override;

    virtual void deleteShaderProgram(ShaderProgram& shaderProgram) const override;

    virtual Mesh createMesh(const float* vertices, uint32_t vertexCount, const float* normals, const float* tangents, const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const override;

    virtual void deleteMesh(Mesh& mesh) const override;

    virtual Texture createTexture(TextureType type, TextureFormat format, unsigned char* data, glm::uvec2 size, bool generateMipmap, TextureFilter filter, TextureWrap wrap) const override;

    virtual void bindTexture(TextureType type, const Texture& texture, unsigned slot) const override;

    virtual void deleteTexture(Texture& texure) const override;

    virtual void submitLight(const RendererDirectionalLight& light) override;

    virtual void submitLight(const RendererPointLight& light) override;

    virtual void submitLight(const RendererSpotLight& light) override;

    virtual void logError(const char* location) const override;

private:
    Ref<ShaderProgram> m_currentShaderProgram;
    Ref<Mesh> m_currentMesh;
    double m_time = 0.0;
    glm::vec3 m_cameraPosition = glm::vec3(0.0f);
    glm::mat4 m_viewMatrix = glm::mat4(1.0);
    glm::mat4 m_projectionMatrix = glm::mat4(1.0);

    std::vector<RendererDirectionalLight> m_directionalLights;
    std::vector<RendererPointLight> m_pointLights;
    std::vector<RendererSpotLight> m_spotLights;

    void bindDirectionalLights();

    void bindPointLights();

    void bindSpotLights();
};

}  // namespace labeeri::Engine
