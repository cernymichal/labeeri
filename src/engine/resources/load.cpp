#include "load.h"

#include <GL/glew.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <sstream>

#include "resources.h"

namespace labeeri::engine {

struct Shader {
    Shader(GLuint shader) : m_shader(shader) {
    }

    Shader(const Shader&) = delete;

    Shader(Shader&& other) noexcept : m_shader(other.m_shader) {
        other.m_shader = 0;
    }

    ~Shader() {
        glDeleteShader(m_shader);
    }

    operator GLuint() const {
        return m_shader;
    }

private:
    GLuint m_shader;
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

    LAB_LOG_OGL_ERROR();

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

    LAB_LOG_OGL_ERROR();

    linkShaderProgram(program);

    return program;
}

ShaderProgram loadShaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::vector<Shader> shaders;
    shaders.emplace_back(loadShader(vertexPath, GL_VERTEX_SHADER));
    shaders.emplace_back(loadShader(fragmentPath, GL_FRAGMENT_SHADER));

    return createShaderProgram(shaders);
}

Mesh loadMesh(const char* filePath) {
    Assimp::Importer importer;

    // normalize size
    // importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate                 // Triangulate polygons (if any).
                                                           | aiProcess_PreTransformVertices  // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
                                                           | aiProcess_GenSmoothNormals      // Calculate normals per vertex.
                                                           | aiProcess_JoinIdenticalVertices);

    if (scene == NULL) {
        LAB_LOG("assimp error: " << importer.GetErrorString());
        throw std::runtime_error("assimp error");
    }

    if (scene->mNumMeshes != 1) {
        LAB_LOG("Can only load one mesh at a time");
        throw std::runtime_error("More than one mesh in file");
    }

    const aiMesh* assimpMesh = scene->mMeshes[0];
    uint32_t vertexCount = assimpMesh->mNumVertices;
    uint32_t faceCount = assimpMesh->mNumFaces;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float) * vertexCount, 0, GL_STATIC_DRAW);  // vertices, normals, and UVs
    // vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vertexCount, assimpMesh->mVertices);
    // normals
    if (assimpMesh->HasNormals())
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vertexCount, 3 * sizeof(float) * vertexCount, assimpMesh->mNormals);
    // UVs
    if (assimpMesh->HasTextureCoords(0)) {
        std::vector<float> UVs;
        UVs.reserve((size_t)vertexCount * 2);

        for (size_t i = 0; i < vertexCount; i++) {
            aiVector3D vector = (assimpMesh->mTextureCoords[0])[i];
            UVs.push_back(vector.x);
            UVs.push_back(vector.y);
        }

        glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float) * vertexCount, sizeof(float) * vertexCount, &UVs[0]);
    }

    LAB_LOG_OGL_ERROR();

    // EBO
    {
        std::vector<unsigned int> indices;
        indices.reserve((size_t)assimpMesh->mNumFaces * 3);

        for (size_t i = 0; i < assimpMesh->mNumFaces; i++) {
            indices.push_back(assimpMesh->mFaces[i].mIndices[0]);
            indices.push_back(assimpMesh->mFaces[i].mIndices[1]);
            indices.push_back(assimpMesh->mFaces[i].mIndices[2]);
        }

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        LAB_LOG_OGL_ERROR();
    }

    auto shader = Shaders::basic();
    if (!shader)
        throw std::runtime_error("No basic shader for default attribute positions");

    GLuint positionLocation = glGetAttribLocation(*shader, "position_in");
    GLuint normalLocation = glGetAttribLocation(*shader, "normal_in");
    GLuint UVLocation = glGetAttribLocation(*shader, "UV_in");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    LAB_LOG_OGL_ERROR();

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float) * vertexCount));

    glEnableVertexAttribArray(UVLocation);
    glVertexAttribPointer(UVLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float) * vertexCount));

    LAB_LOG_OGL_ERROR();

    glBindVertexArray(0);

    return Mesh(VAO, VBO, EBO, faceCount);
}

}  // namespace labeeri::engine
