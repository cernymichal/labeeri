#include "Material.h"

#include <GL/glew.h>

namespace labeeri::Engine {

ShaderProgram::ShaderProgram(LAB_GL_HANDLE program) : m_program(program) {
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept : m_program(other.m_program) {
    other.m_program = 0;
}

ShaderProgram::~ShaderProgram() {
    // individual shaders are deleted when the program is linked
    /*
    int shaderCount = 0;
    GLuint shaders[MAX_PROGRAM_SHADER_COUNT];
    glGetAttachedShaders(m_program, MAX_PROGRAM_SHADER_COUNT, &shaderCount, shaders);
    for (int i = 0; i < shaderCount; i++)
        glDeleteShader(shaders[i]);
    */

    glDeleteProgram(m_program);
}

LAB_GL_INT ShaderProgram::getUniformLocation(const char* name) {
    auto iter = m_uniforms.find(name);

    if (iter != m_uniforms.end())
        return (*iter).second;

    GLint location = glGetUniformLocation(m_program, name);
    if (location != -1)
        m_uniforms[name] = location;

    return location;
}

ShaderProgram::operator LAB_GL_HANDLE() const {
    return m_program;
}

Material::Material(const std::shared_ptr<ShaderProgram>& shader) : m_shader(shader) {
}

void Material::bindUniforms(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;

    const glm::mat4 modelRotationMatrix = glm::mat4(
        modelMatrix[0],
        modelMatrix[1],
        modelMatrix[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

    glUniform1f(m_shader->getUniformLocation("time"), (float)time);
    glUniformMatrix4fv(m_shader->getUniformLocation("PVM_matrix"), 1, GL_FALSE, glm::value_ptr(PVM));
    glUniformMatrix4fv(m_shader->getUniformLocation("view_matrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("model_matrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    LAB_LOG_OGL_ERROR();
}

}  // namespace labeeri::Engine