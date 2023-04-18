#include "Material.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(GLuint program) : m_program(program) {
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}

GLint Shader::getUniformLocation(const char* name) {
    auto iter = m_uniforms.find(name);

    if (iter != m_uniforms.end())
        return (*iter).second;

    GLint location = glGetUniformLocation(m_program, name);
    if (location != -1)
        m_uniforms[name] = location;

    return location;
}

Material::Material(const std::shared_ptr<Shader>& shader) : m_shader(shader) {
}

void Material::bindUniforms(double time, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;

    const glm::mat4 modelRotationMatrix = glm::mat4(
        modelMatrix[0],
        modelMatrix[1],
        modelMatrix[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

    glUniform1f(m_shader->getUniformLocation("time"), time);
    glUniformMatrix4fv(m_shader->getUniformLocation("PVM_matrix"), 1, GL_FALSE, glm::value_ptr(PVM));
    glUniformMatrix4fv(m_shader->getUniformLocation("view_matrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("model_matrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(m_shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}
