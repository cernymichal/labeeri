#include "GLRenderer.h"

#include <glad/glad.h>

#include "Engine/Resources/Resources.h"
#include "Engine/Window/IWindow.h"

namespace labeeri::Engine {

struct Shader {
    explicit Shader(GLuint shader) : m_shader(shader) {
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

Shader compileShader(const char* source, ShaderType shaderType) {
    int type;
    const char* typeStr;
    switch (shaderType) {
        case (ShaderType::Vertex):
            type = GL_VERTEX_SHADER;
            typeStr = "vertex";
            break;
        case (ShaderType::Fragment):
            type = GL_FRAGMENT_SHADER;
            typeStr = "fragment";
            break;
        case (ShaderType::Geometry):
            type = GL_GEOMETRY_SHADER;
            typeStr = "geometry";
            break;
        default:
            throw std::runtime_error("Unknown shader type");
    }

    Shader shader(glCreateShader(type));
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    LAB_LOG_RENDERAPI_ERROR();

    if (status == GL_TRUE) {
        LAB_LOG(typeStr << " shader compiled");
        return shader;
    }

    // compilation failed

    GLint infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    auto infoLogStr = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLogStr);

    LAB_LOG("Failed to compile " << typeStr << " shader:");
    LAB_LOG(infoLogStr);

    delete[] infoLogStr;

    throw std::runtime_error("Failed to compile shader");
}

void linkShaderProgram(GLuint program) {
    glLinkProgram(program);

    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_TRUE) {
        LAB_LOG("Shader program linked");
        return;
    }
    // linking failed

    GLint infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    auto strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog(program, infoLogLength, nullptr, strInfoLog);

    LAB_LOG("Linker failure: " << strInfoLog);
    delete[] strInfoLog;

    throw std::runtime_error("Failed to link shader program");
}

int clearBuffersGL(int buffers) {
    int buffersGL = 0;
    if (buffers & static_cast<int>(ClearBuffer::Color))
        buffersGL |= GL_COLOR_BUFFER_BIT;
    if (buffers & static_cast<int>(ClearBuffer::Depth))
        buffersGL |= GL_DEPTH_BUFFER_BIT;
    if (buffers & static_cast<int>(ClearBuffer::Stencil))
        buffersGL |= GL_STENCIL_BUFFER_BIT;

    return buffersGL;
}

int textureTypeGL(TextureType type) {
    switch (type) {
        case TextureType::Texture2D:
            return GL_TEXTURE_2D;
        case TextureType::Rectangle:
            return GL_TEXTURE_RECTANGLE;
        case TextureType::Cubemap:
            return GL_TEXTURE_CUBE_MAP;
        default:
            throw std::runtime_error("Unknown texture type");
    }
}

int textureInternalFormatGL(TextureInternalFormat format) {
    switch (format) {
        case TextureInternalFormat::RGB:
            return GL_RGB;
        case TextureInternalFormat::RGBA:
            return GL_RGBA;
        case TextureInternalFormat::SRGB:
            return GL_SRGB;
        case TextureInternalFormat::SRGBA:
            return GL_SRGB_ALPHA;
        case TextureInternalFormat::RGBFloat16:
            return GL_RGB16F;
        case TextureInternalFormat::RGBAFloat16:
            return GL_RGBA16F;
        case TextureInternalFormat::RGBFloat32:
            return GL_RGB32F;
        case TextureInternalFormat::RGBAFloat32:
            return GL_RGBA32F;
        case TextureInternalFormat::RedUInt32:
            return GL_R32UI;
        case TextureInternalFormat::DepthFloat32:
            return GL_DEPTH_COMPONENT32F;
        default:
            throw std::runtime_error("Unknown texture internal format");
    }
}

int textureFormatGL(TextureFormat format) {
    switch (format) {
        case TextureFormat::Red:
            return GL_RED;
        case TextureFormat::RGB:
            return GL_RGB;
        case TextureFormat::RGBA:
            return GL_RGBA;
        case TextureFormat::RedInt:
            return GL_RED_INTEGER;
        case TextureFormat::Depth:
            return GL_DEPTH_COMPONENT;
        default:
            throw std::runtime_error("Unknown texture format");
    }
}

int textureDataTypeGL(TextureDataType type) {
    switch (type) {
        case TextureDataType::UByte:
            return GL_UNSIGNED_BYTE;
        case TextureDataType::UInt32:
            return GL_UNSIGNED_INT;
        case TextureDataType::Float16:
            return GL_HALF_FLOAT;
        case TextureDataType::Float32:
            return GL_FLOAT;
        default:
            throw std::runtime_error("Unknown texture data type");
    }
}

std::pair<int, int> textureFilterGL(TextureFilter filter, bool usingMipmap) {
    int minFilterGL, magFilterGL;
    switch (filter) {
        case TextureFilter::Nearest:
            minFilterGL = usingMipmap ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST;
            magFilterGL = GL_NEAREST;
            break;
        case TextureFilter::Linear:
            minFilterGL = usingMipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
            magFilterGL = GL_LINEAR;
            break;
        default:
            throw std::runtime_error("Unknown texture filtering mode");
    }

    return {minFilterGL, magFilterGL};
}

int textureWrapGL(TextureWrap wrap) {
    switch (wrap) {
        case TextureWrap::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        case TextureWrap::Repeat:
            return GL_REPEAT;
        case TextureWrap::MirroredRepeat:
            return GL_MIRRORED_REPEAT;
        default:
            throw std::runtime_error("Unknown texture wrapping mode");
    }
}

GLRenderer::GLRenderer() {
    LAB_LOGH3("GLRenderer::GLRenderer()");

    if (!gladLoadGLLoader((GLADloadproc)LAB_WINDOW->procAddressGetter()))
        throw std::runtime_error("gladLoadGLLoader failed");

    LAB_LOG("OpenGL version: " << glGetString(GL_VERSION));
    LAB_LOG("Shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION));
    LAB_LOG("Vendor: " << glGetString(GL_VENDOR));
    LAB_LOG("Renderer: " << glGetString(GL_RENDERER));

    glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void GLRenderer::clear(int buffers) {
    glClearDepth(0.0f);
    glClear(clearBuffersGL(buffers));
}

void GLRenderer::clearBuffer(int buffers, uint32_t value) {
    int buffersGL = 0;
    if (buffers & static_cast<int>(ClearBuffer::Color))
        buffersGL |= GL_COLOR;
    if (buffers & static_cast<int>(ClearBuffer::Depth))
        buffersGL |= GL_DEPTH;
    if (buffers & static_cast<int>(ClearBuffer::Stencil))
        buffersGL |= GL_STENCIL;

    glClearBufferuiv(buffersGL, 0, &value);
}

void GLRenderer::setClearColor(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void GLRenderer::beginScene(double time, const glm::vec3& cameraPosition, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const RenderSceneParameters& parameters) {
    m_time = time;
    m_cameraPosition = cameraPosition;
    m_matrices.view = viewMatrix;
    m_matrices.viewInverse = glm::inverse(m_matrices.view);
    m_matrices.projection = projectionMatrix;
    m_matrices.projectionInverse = glm::inverse(projectionMatrix);
    m_sceneParameters = parameters;

    if (!m_postprocessShader)
        initialize();

    m_currentShaderProgram = nullptr;
    m_currentMesh = nullptr;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glDepthMask(GL_TRUE);
}

void GLRenderer::endOpaque() {
    drawSkybox();
    glDepthMask(GL_FALSE);
}

void GLRenderer::endScene() {
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_directionalLights.clear();
    m_pointLights.clear();
    m_spotLights.clear();
}

void GLRenderer::drawToScreen() const {
    glm::uvec2 frameSize = m_currentFramebuffer->m_size;
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, *m_currentFramebuffer);
    glBlitFramebuffer(0, 0, frameSize.x, frameSize.y, 0, 0, frameSize.x, frameSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLRenderer::drawToScreenPostprocessed() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    useShaderProgram(m_postprocessShader);
    bindMesh(m_screenQuad);
    bindTexture(TextureType::Texture2D, *m_currentFramebuffer->m_attachments.at(FramebufferAttachment::Color), 0);
    bindUniform("u_color_buffer", 0);
    bindTexture(TextureType::Texture2D, *m_currentFramebuffer->m_attachments.at(FramebufferAttachment::Depth), 1);
    bindUniform("u_depth_buffer", 1);
    bindUniform("u_gamma", m_sceneParameters.postprocessing.gamma);
    bindUniform("u_exposure", m_sceneParameters.postprocessing.exposure);
    drawMesh();
}

void GLRenderer::waitForFrame() {
    glFlush();
    glFinish();
}

void GLRenderer::useShaderProgram(const Ref<ShaderProgram>& shaderProgram) {
    if (m_currentShaderProgram == shaderProgram)
        return;

    m_currentShaderProgram = shaderProgram;
    glUseProgram(*m_currentShaderProgram);

    bindUniform("u_time", (float)m_time);
    bindUniform("u_camera_position", m_cameraPosition);
    bindUniform("u_view_matrix", m_matrices.view);
    bindUniform("u_view_matrix_inverse", m_matrices.viewInverse);
    bindUniform("u_projection_matrix_inverse", m_matrices.projectionInverse);
    bindUniform("u_screen_size", m_currentFramebuffer->m_size);

    bindDirectionalLights();
    bindPointLights();
    bindSpotLights();
    bindFog();

    if (m_sceneParameters.skybox) {
        bindTexture(TextureType::Cubemap, *m_sceneParameters.skybox, 0);
        bindUniform("u_cubemap", 0);
    }
    bindUniform("u_using_cubemap", m_sceneParameters.skybox != nullptr);
}

void GLRenderer::bindUniform(const char* name, float value) {
    glUniform1f(m_currentShaderProgram->getUniformLocation(name), value);
}

void GLRenderer::bindUniform(const char* name, int32_t value) {
    glUniform1i(m_currentShaderProgram->getUniformLocation(name), value);
}

void GLRenderer::bindUniform(const char* name, uint32_t value) {
    glUniform1ui(m_currentShaderProgram->getUniformLocation(name), value);
}

void GLRenderer::bindUniform(const char* name, const glm::mat4& value) {
    glUniformMatrix4fv(m_currentShaderProgram->getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void GLRenderer::bindUniform(const char* name, const glm::vec2& value) {
    glUniform2fv(m_currentShaderProgram->getUniformLocation(name), 1, glm::value_ptr(value));
}

void GLRenderer::bindUniform(const char* name, const glm::vec3& value) {
    glUniform3fv(m_currentShaderProgram->getUniformLocation(name), 1, glm::value_ptr(value));
}

void GLRenderer::bindPVM(const glm::mat4& modelMatrix) {
    glm::mat4 PVM = m_matrices.projection * m_matrices.view * modelMatrix;

    const glm::mat4 modelRotationMatrix = glm::mat4(
        modelMatrix[0],
        modelMatrix[1],
        modelMatrix[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

    bindUniform("u_PVM_matrix", PVM);
    bindUniform("u_model_matrix", modelMatrix);
    bindUniform("u_normal_matrix", normalMatrix);
}

LAB_GL_INT GLRenderer::getUniformLocation(ShaderProgram& shaderProgram, const char* name) {
    return glGetUniformLocation(shaderProgram, name);
}

void GLRenderer::bindMesh(const Ref<Mesh>& mesh) {
    if (m_currentMesh == mesh)
        return;

    m_currentMesh = mesh;
    glBindVertexArray(mesh->m_vertexArrayObject);
}

void GLRenderer::drawMesh() {
    glDrawElements(GL_TRIANGLES, m_currentMesh->m_triangleCount * 3, GL_UNSIGNED_INT, nullptr);
}

ShaderProgram GLRenderer::createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const {
    ShaderProgram program(glCreateProgram());

    for (const auto& [source, type] : shaders) {
        Shader compiledShader = compileShader(type, source);
        glAttachShader(program, compiledShader);
    }

    LAB_LOG_RENDERAPI_ERROR();

    linkShaderProgram(program);

    return program;
}

void GLRenderer::deleteShaderProgram(ShaderProgram& shaderProgram) const {
    glDeleteProgram(shaderProgram);
}

Mesh GLRenderer::createMesh(const float* vertices, uint32_t vertexCount,
                            const float* normals, const float* tangents,
                            const std::vector<const float*>& uvs, const unsigned int* indices, uint32_t faceCount) const {
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 11 * sizeof(float) * vertexCount, nullptr, GL_STATIC_DRAW);  // vertices, normals, tangents and UVs

    // vertices
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * vertexCount, vertices);
    LAB_LOG("Uploaded vertices");

    // normals
    if (normals) {
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vertexCount, 3 * sizeof(float) * vertexCount, normals);
        LAB_LOG("Uploaded normals");
    }

    // tangents
    if (tangents) {
        glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float) * vertexCount, 3 * sizeof(float) * vertexCount, tangents);
        LAB_LOG("Uploaded tangents");
    }

    // UVs
    for (const auto& map : uvs) {  // TODO more than one UV map
        glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float) * vertexCount, 2 * sizeof(float) * vertexCount, map);
        LAB_LOG("Uploaded UV map");
    }

    LAB_LOG_RENDERAPI_ERROR();

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faceCount * 3, indices, GL_STATIC_DRAW);

    LAB_LOG_RENDERAPI_ERROR();
    LAB_LOG("Uploaded " << faceCount << " faces");

    auto& shader = Resources<ShaderProgram>::get("phong");
    if (!shader)
        throw std::runtime_error("No phong shader for default attribute positions");

    GLuint positionLocation = glGetAttribLocation(*shader, "in_position");
    GLuint normalLocation = glGetAttribLocation(*shader, "in_normal");
    GLuint tangentLocation = glGetAttribLocation(*shader, "in_tangent");
    GLuint UVLocation = glGetAttribLocation(*shader, "in_UV");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    LAB_LOG_RENDERAPI_ERROR();

    glEnableVertexAttribArray(positionLocation);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float) * vertexCount));

    glEnableVertexAttribArray(tangentLocation);
    glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float) * vertexCount));

    glEnableVertexAttribArray(UVLocation);
    glVertexAttribPointer(UVLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(9 * sizeof(float) * vertexCount));

    LAB_LOG_RENDERAPI_ERROR();
    LAB_LOG("Attribute pointers created");

    glBindVertexArray(0);
    LAB_LOG(VAO);
    return Mesh(VAO, VBO, EBO, faceCount);
}

void GLRenderer::deleteMesh(Mesh& mesh) const {
    glDeleteVertexArrays(1, &mesh.m_vertexArrayObject);
    glDeleteBuffers(1, &mesh.m_vertexBufferObject);
    glDeleteBuffers(1, &mesh.m_elementBufferObject);
}

Texture GLRenderer::createTexture(TextureType type, const Image& image, bool generateMipmap,
                                  TextureFilter filter, TextureWrap wrap) const {
    int typeGL = textureTypeGL(type);
    int internalFormatGL = textureInternalFormatGL(image.internalFormat);
    int formatGL = textureFormatGL(image.format);
    int dataTypeGL = textureDataTypeGL(image.dataType);
    auto [minFilterGL, magFilterGL] = textureFilterGL(filter, generateMipmap);
    int wrapGL = textureWrapGL(wrap);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(typeGL, texture);

    glTexParameteri(typeGL, GL_TEXTURE_WRAP_S, wrapGL);
    glTexParameteri(typeGL, GL_TEXTURE_WRAP_T, wrapGL);
    glTexParameteri(typeGL, GL_TEXTURE_MIN_FILTER, minFilterGL);
    glTexParameteri(typeGL, GL_TEXTURE_MAG_FILTER, magFilterGL);

    glTexImage2D(typeGL, 0, internalFormatGL, image.size.x, image.size.y, 0, formatGL, dataTypeGL, image.data);
    if (generateMipmap)
        glGenerateMipmap(typeGL);

    LAB_LOG_RENDERAPI_ERROR();
    glBindTexture(typeGL, 0);

    return Texture(texture);
}

Texture GLRenderer::createCubemap(const std::array<Scoped<Image>, 6>& images, TextureFilter filter) const {
    int internalFormatGL = textureInternalFormatGL(images[0]->internalFormat);
    int formatGL = textureFormatGL(images[0]->format);
    int dataTypeGL = textureDataTypeGL(images[0]->dataType);
    auto [minFilterGL, magFilterGL] = textureFilterGL(filter, false);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilterGL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilterGL);

    for (int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormatGL, images[i]->size.x, images[i]->size.y, 0,
                     formatGL, dataTypeGL, images[i]->data);
    }

    LAB_LOG_RENDERAPI_ERROR();
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return Texture(texture);
}

void GLRenderer::bindTexture(TextureType type, const Texture& texture, unsigned slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(textureTypeGL(type), texture);
}

void GLRenderer::readFramebuffer(TextureFormat format, TextureDataType dataType,
                                 glm::uvec2 position, glm::uvec2 size, void* result) const {
    int formatGL = textureFormatGL(format);
    int dataTypeGL = textureDataTypeGL(dataType);

    glReadPixels(position.x, position.y, size.x, size.y, formatGL, dataTypeGL, result);
}

void GLRenderer::deleteTexture(Texture& texure) const {
    GLuint texureGL = texure;
    glDeleteTextures(1, &texureGL);
}

Framebuffer GLRenderer::createFramebuffer(glm::uvec2 size, std::map<FramebufferAttachment, Ref<Texture>>&& attachments) const {
    GLuint FBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    if (attachments.count(FramebufferAttachment::Color) != 0)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *attachments.at(FramebufferAttachment::Color), 0);
    if (attachments.count(FramebufferAttachment::Depth) != 0)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *attachments.at(FramebufferAttachment::Depth), 0);
    if (attachments.count(FramebufferAttachment::Stencil) != 0)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, *attachments.at(FramebufferAttachment::Stencil), 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        LAB_LOG("Framebuffer not complete: " << status);

    glViewport(0, 0, size.x, size.y);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return Framebuffer(FBO, size, attachments);
}

void GLRenderer::bindFramebuffer(const Ref<Framebuffer>& framebuffer) {
    m_currentFramebuffer = framebuffer;
    glBindFramebuffer(GL_FRAMEBUFFER, *m_currentFramebuffer);
    glViewport(0, 0, m_currentFramebuffer->m_size.x, m_currentFramebuffer->m_size.y);
}

void GLRenderer::deleteFramebuffer(Framebuffer& framebuffer) const {
    GLuint FBO = framebuffer;
    glDeleteFramebuffers(1, &FBO);
}

void GLRenderer::submitLight(const RendererDirectionalLight& light) {
    if (m_directionalLights.size() >= MAX_DIRECTIONAL_LIGHTS) {
        LAB_LOG("Directional light limit reached!");
        return;
    }

    m_directionalLights.emplace_back(light);
}

void GLRenderer::submitLight(const RendererPointLight& light) {
    if (m_pointLights.size() >= MAX_POINT_LIGHTS) {
        LAB_LOG("Point light limit reached!");
        return;
    }

    m_pointLights.emplace_back(light);
}

void GLRenderer::submitLight(const RendererSpotLight& light) {
    if (m_spotLights.size() >= MAX_SPOT_LIGHTS) {
        LAB_LOG("Spot light limit reached!");
        return;
    }

    m_spotLights.emplace_back(light);
}

void GLRenderer::logError(const char* location) const {
    for (GLenum error = glGetError(); error != GL_NO_ERROR; error = glGetError()) {
        std::string errorStr = "UNKNOWN";
        switch (error) {
            case GL_INVALID_ENUM:
                errorStr = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorStr = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorStr = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                errorStr = "GL_OUT_OF_MEMORY";
                break;
            default:;
        }

        LAB_LOG("OpenGL error: " << errorStr << " at " << location);
    }
}

void GLRenderer::initialize() {
    m_screenQuad = makeRef<Mesh>(createScreenQuad());
    m_skyboxShader = Resources<ShaderProgram>::get("skybox");
    m_postprocessShader = Resources<ShaderProgram>::get("postprocess");
}

void GLRenderer::bindDirectionalLights() {
    if (m_currentShaderProgram->getUniformLocation("u_directional_light_count") == -1)
        return;

    bindUniform("u_directional_light_count", static_cast<int>(m_directionalLights.size()));
    for (int i = 0; i < m_directionalLights.size(); i++) {
        const auto& light = m_directionalLights[i];
        const std::string structLocation = std::format("u_directional_lights[{}]", i);
        std::string location = structLocation + ".direction";
        bindUniform(location.c_str(), light.direction);
        location = structLocation + ".properties.ambient";
        bindUniform(location.c_str(), light.properties.ambient);
        location = structLocation + ".properties.diffuse";
        bindUniform(location.c_str(), light.properties.diffuse);
        location = structLocation + ".properties.specular";
        bindUniform(location.c_str(), light.properties.specular);
    }
}

Mesh GLRenderer::createScreenQuad() const {
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f};

    float UVs[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    return createMesh(vertices, 4, nullptr, nullptr, {UVs}, indices, 2);
}

void GLRenderer::bindPointLights() {
    if (m_currentShaderProgram->getUniformLocation("u_point_light_count") == -1)
        return;

    bindUniform("u_point_light_count", static_cast<int>(m_pointLights.size()));
    for (int i = 0; i < m_pointLights.size(); i++) {
        const auto& light = m_pointLights[i];
        const std::string structLocation = std::format("u_point_lights[{}]", i);
        std::string location = structLocation + ".position";
        bindUniform(location.c_str(), light.position);
        location = structLocation + ".properties.ambient";
        bindUniform(location.c_str(), light.properties.ambient);
        location = structLocation + ".properties.diffuse";
        bindUniform(location.c_str(), light.properties.diffuse);
        location = structLocation + ".properties.specular";
        bindUniform(location.c_str(), light.properties.specular);
        location = structLocation + ".attenuation.constant";
        bindUniform(location.c_str(), light.attenuation.constant);
        location = structLocation + ".attenuation.linear";
        bindUniform(location.c_str(), light.attenuation.linear);
        location = structLocation + ".attenuation.quadratic";
        bindUniform(location.c_str(), light.attenuation.quadratic);
    }
}

void GLRenderer::bindSpotLights() {
    if (m_currentShaderProgram->getUniformLocation("u_spot_light_count") == -1)
        return;

    bindUniform("u_spot_light_count", static_cast<int>(m_spotLights.size()));
    for (int i = 0; i < m_spotLights.size(); i++) {
        const auto& light = m_spotLights[i];
        const std::string structLocation = std::format("u_spot_lights[{}]", i);
        std::string location = structLocation + ".position";
        bindUniform(location.c_str(), light.position);
        location = structLocation + ".direction";
        bindUniform(location.c_str(), light.direction);
        location = structLocation + ".innerCutoff";
        bindUniform(location.c_str(), light.innerCutoff);
        location = structLocation + ".outerCutoff";
        bindUniform(location.c_str(), light.outerCutoff);
        location = structLocation + ".properties.ambient";
        bindUniform(location.c_str(), light.properties.ambient);
        location = structLocation + ".properties.diffuse";
        bindUniform(location.c_str(), light.properties.diffuse);
        location = structLocation + ".properties.specular";
        bindUniform(location.c_str(), light.properties.specular);
        location = structLocation + ".attenuation.constant";
        bindUniform(location.c_str(), light.attenuation.constant);
        location = structLocation + ".attenuation.linear";
        bindUniform(location.c_str(), light.attenuation.linear);
        location = structLocation + ".attenuation.quadratic";
        bindUniform(location.c_str(), light.attenuation.quadratic);
    }
}

void GLRenderer::bindFog() {
    if (m_currentShaderProgram->getUniformLocation("u_fog.color") == -1)
        return;

    const std::string structLocation = "u_fog";
    std::string location = structLocation + ".color";
    bindUniform(location.c_str(), m_sceneParameters.fog.color);
    location = structLocation + ".density";
    bindUniform(location.c_str(), m_sceneParameters.fog.density);
}

void GLRenderer::drawSkybox() {
    if (!m_sceneParameters.skybox)
        return;

    glDepthFunc(GL_GEQUAL);
    useShaderProgram(m_skyboxShader);
    bindMesh(m_screenQuad);
    drawMesh();
    glDepthFunc(GL_GREATER);
}

}  // namespace labeeri::Engine