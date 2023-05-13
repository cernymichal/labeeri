#include "ShaderProgram.h"

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

ShaderProgram::~ShaderProgram() {
    LAB_RENDERER->deleteShaderProgram(*this);
}

LAB_GL_INT ShaderProgram::getUniformLocation(const std::string& name) {
    auto iter = m_uniforms.find(name);

    if (iter != m_uniforms.end())
        return (*iter).second;

    LAB_GL_INT location = LAB_RENDERER->getUniformLocation(*this, name.c_str());
    if (location != -1)
        m_uniforms[name] = location;

    return location;
}

}  // namespace labeeri::Engine