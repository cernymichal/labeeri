#include "load.h"

#include <GL/glew.h>

#include <algorithm>
#include <fstream>
#include <sstream>

#include "log.h"

struct Shader {
    Shader(GLint shader) : m_shader(shader) {
    }

    Shader(const Shader&) = delete;

    Shader(Shader&& other) noexcept : m_shader(other.m_shader) {
        other.m_shader = 0;
    }

    ~Shader() {
        glDeleteShader(m_shader);
    }

    operator GLint() const {
        return m_shader;
    }

private:
    GLint m_shader;
};

Shader loadShader(const char* path, GLenum shaderType) {
    std::ifstream file(path);
    std::stringstream contentBuffer;

    if (!file.good()) {
        LAB_LOG("Failed to open file " << path);
        throw std::runtime_error("Failed to open file");
    }

    contentBuffer << file.rdbuf();
    std::string content = contentBuffer.str();
    const char* contentPtr = content.c_str();

    Shader shader(glCreateShader(shaderType));
    glShaderSource(shader, 1, &contentPtr, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_TRUE)
        return shader;

    // compilation failed

    GLint infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

    const char* strShaderType = NULL;
    switch (shaderType) {
        case GL_VERTEX_SHADER:
            strShaderType = "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            strShaderType = "fragment";
            break;
        case GL_GEOMETRY_SHADER:
            strShaderType = "geometry";
            break;
    }

    LAB_LOG("Failed to compile " << strShaderType << " shader " << path << ":");
    LAB_LOG(strInfoLog);

    delete[] strInfoLog;

    throw std::runtime_error("Failed to compile shader");
}

void linkShaderProgram(GLuint program) {
    glLinkProgram(program);

    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_TRUE)
        return;

    // linking failed

    GLint infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar* strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

    LAB_LOG("Linker failure: " << strInfoLog);
    delete[] strInfoLog;

    throw std::runtime_error("Failed to link shader program");
}

ShaderProgram createShaderProgram(const std::vector<Shader>& shaders) {
    ShaderProgram program(glCreateProgram());

    for (const auto& shader : shaders)
        glAttachShader(program, shader);

    linkShaderProgram(program);

    return program;
}

namespace load {

ShaderProgram shaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::vector<Shader> shaders;
    shaders.emplace_back(loadShader(vertexPath, GL_VERTEX_SHADER));
    shaders.emplace_back(loadShader(fragmentPath, GL_FRAGMENT_SHADER));

    return createShaderProgram(shaders);
}

Mesh mesh(const char* filePath) {
    // TODO
    return Mesh(0, 0, 0, 0);
}

}  // namespace load
