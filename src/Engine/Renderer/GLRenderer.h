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

    virtual void beginScene(double time, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    virtual void endScene() override;

    virtual void useShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) override;

    virtual void bindUniform(const char* name, float value) override;

    virtual void bindUniform(const char* name, const glm::mat4& value) override;

    virtual void bindUniform(const char* name, const glm::vec3& value) override;

    virtual void bindPVM(const glm::mat4& modelMatrix) override;

    virtual LAB_GL_INT getUniformLocation(ShaderProgram& shaderProgram, const char* name) override;

    virtual void bindMesh(const Mesh& mesh) override;

    virtual void drawMesh(const Mesh& mesh) override;

    virtual ShaderProgram createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const override;

    virtual void deleteShaderProgram(ShaderProgram& shaderProgram) const override;

    virtual Mesh createMesh(const float* vertices, uint32_t vertexCount, const float* normals, const std::vector<const float*> UVs, const unsigned int* indices, uint32_t faceCount) const override;

    virtual void deleteMesh(Mesh& mesh) const override;

private:
    std::shared_ptr<ShaderProgram> m_currentShaderProgram;
    double m_time = 0.0;
    glm::mat4 m_viewMatrix = glm::mat4(1.0);
    glm::mat4 m_projectionMatrix = glm::mat4(1.0);
};

}  // namespace labeeri::Engine
