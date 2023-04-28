#include "Material.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

ShaderProgram::ShaderProgram(LAB_GL_HANDLE program) : m_program(program) {
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept : m_program(other.m_program) {
    other.m_program = 0;
}

ShaderProgram::~ShaderProgram() {
    LAB_RENDERER->deleteShaderProgram(*this);
}

LAB_GL_INT ShaderProgram::getUniformLocation(const char* name) {
    auto iter = m_uniforms.find(name);

    if (iter != m_uniforms.end())
        return (*iter).second;

    LAB_GL_INT location = LAB_RENDERER->getUniformLocation(*this, name);
    if (location != -1)
        m_uniforms[name] = location;

    return location;
}

ShaderProgram::operator LAB_GL_HANDLE() const {
    return m_program;
}

Material::Material(const std::shared_ptr<ShaderProgram>& shader) : m_shader(shader) {
}

void Material::bindUniforms() {
}

}  // namespace labeeri::Engine