#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

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
    virtual void beginScene(double time, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

    /**
     * @brief TODO
     */
    virtual void endScene() = 0;

    /**
     * @brief TODO
     */
    virtual void useShaderProgram(const std::shared_ptr<ShaderProgram>& shaderProgram) = 0;

    /**
     * @brief TODO
     */
    virtual void bindUniform(const char* name, float value) = 0;

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
    virtual void bindMesh(const Mesh& mesh) = 0;

    /**
     * @brief TODO
     */
    virtual void drawMesh(const Mesh& mesh) = 0;

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
    static inline IRenderer* get() {
        return s_renderer.get();
    }

private:
    static std::unique_ptr<IRenderer> s_renderer;

    friend Application;
};

}  // namespace labeeri::Engine
