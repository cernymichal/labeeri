#pragma once

#include "Renderer/Framebuffer.h"
#include "Renderer/ImageResource.h"
#include "Renderer/Light.h"
#include "Renderer/MeshResource.h"
#include "Renderer/RendererParameters.h"
#include "Renderer/ShaderResource.h"
#include "Renderer/TextureResource.h"

namespace labeeri {

class Application;

/**
 * @brief Render API abstarction interface.
 */
class IRenderer {
public:
    virtual ~IRenderer() = default;

    /**
     * @brief Clears buffers.
     *
     * @param buffers The buffers to clear.
     */
    virtual void clear(i32 buffers) = 0;

    /**
     * @brief Clears buffers with a value.
     *
     * @param buffers The buffers to clear.
     * @param value The value to clear the buffers with.
     */
    virtual void clearBuffer(i32 buffers, u32 value) = 0;

    /**
     * @brief Sets the clear color.
     *
     * @param color The clear color.
     */
    virtual void setClearColor(const vec4& color) = 0;

    /**
     * @brief Start a new scene render.
     *
     * @param currentTime The time in the scene.
     * @param cameraPosition The position of the camera.
     * @param viewMatrix The view matrix of the camera.
     * @param projectionMatrix The projection matrix of the camera.
     * @param parameters The parameters of the scene.
     */
    virtual void beginScene(f64 currentTime, const vec3& cameraPosition, const mat4& viewMatrix, const mat4& projectionMatrix,
                            const RenderSceneParameters& parameters = RenderSceneParameters()) = 0;

    /**
     * @brief Signals the end of rendering opaque objects and the beginning of rendering transparent ones.
     */
    virtual void endOpaque() = 0;

    /**
     * @brief Ends the scene render.
     */
    virtual void endScene() = 0;

    /**
     * @brief Copies the framebuffer to the buffer without postprocessing.
     */
    virtual void drawToScreen() const = 0;

    /**
     * @brief Copies the framebuffer to the buffer postprocessed.
     *
     * @param crosshair Whether to draw the crosshair.
     */
    virtual void drawToScreenPostprocessed(float crosshairScale = 0.0f) = 0;

    /**
     * @brief Waits for the API to flush all the commands.
     */
    virtual void waitForFrame() = 0;

    /**
     * @brief Switches the current shader program.
     *
     * @param shaderProgram The shader program to use.
     */
    virtual void useShaderProgram(const Ref<ShaderResource>& shaderProgram) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, f32 value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, i32 value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, u32 value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, const mat4& value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, const vec2& value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, const uvec2& value) = 0;

    /**
     * @brief Binds a value to uniform.
     *
     * @param name The name of the uniform.
     * @param value The value to bind.
     */
    virtual void bindUniform(const char* name, const vec3& value) = 0;

    /**
     * @brief Binds the PVM matrices uniforms.
     *
     * @param modelMatrix The current model matrix.
     */
    virtual void bindPVM(const mat4& modelMatrix) = 0;

    /**
     * @param shaderProgram The shader program to get the uniform location from.
     * @param name The name of the uniform.
     * @return The uniform location.
     */
    virtual LAB_GL_INT getUniformLocation(ShaderResource& shaderProgram, const char* name) = 0;

    /**
     * @brief Binds a mesh to use.
     *
     * @param mesh The mesh to bind.
     */
    virtual void bindMesh(const Ref<MeshResource>& mesh) = 0;

    /**
     * @brief Draws the current mesh with the current shader program.
     */
    virtual void drawMesh() = 0;

    /**
     * @brief Creates a new shader program.
     *
     * @param shaders The shaders to use.
     * @return The shader program.
     */
    virtual ShaderResource createShaderProgram(const std::vector<std::pair<ShaderType, const char*>>& shaders) const = 0;

    /**
     * @brief Deletes a shader program.
     *
     * @param shaderProgram The shader program to delete.
     */
    virtual void deleteShaderProgram(ShaderResource& shaderProgram) const = 0;

    /**
     * @brief Creates a new mesh.
     *
     * @param vertices The vertices of the mesh.
     * @param vertexCount The number of vertices.
     * @param normals The normals of the mesh.
     * @param tangets The tangents of the mesh.
     * @param uvs The UVs of the mesh.
     * @param indices The indices of the mesh.
     * @param faceCount The number of faces.
     * @return The mesh.
     */
    virtual MeshResource createMesh(const vec3* vertices, u32 vertexCount,
                                    const vec3* normals, const vec4* tangents,
                                    const std::vector<const vec2*>& uvs, const u32* indices, u32 faceCount) const = 0;

    /**
     * @brief Deletes a mesh.
     *
     * @param mesh The mesh to delete.
     */
    virtual void deleteMesh(MeshResource& mesh) const = 0;

    /**
     * @brief Creates a new texture.
     *
     * @param type The type of the texture.
     * @param image The image data of the texture.
     * @param generateMipmap Whether to generate mipmaps.
     * @param filter The filtering to use.
     * @param wrap The wrapping mode to use.
     * @return The texture.
     */
    virtual TextureResource createTexture(TextureType type, const ImageResource& image, bool generateMipmap = true,
                                          TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat) const = 0;

    /**
     * @brief Creates a new cubemap texture.
     *
     * @param images The images of the cubemap.
     * @param filter The filtering to use.
     * @return The texture.
     */
    virtual TextureResource createCubemap(const std::array<Ref<ImageResource>, 6>& images, TextureFilter filter = TextureFilter::Linear) const = 0;

    /**
     * @brief Binds a texture to a slot.
     *
     * @param type The type of the texture.
     * @param texture The texture to bind.
     * @param slot The slot to bind to.
     */
    virtual void bindTexture(TextureType type, const TextureResource& texture, u32 slot = 0) const = 0;

    /**
     * @brief Reads the current framebuffer data.
     *
     * @param format The format of the data.
     * @param dataType The data type of the data.
     * @param position The position to read from.
     * @param size The size to read.
     * @param result The result buffer.
     */
    virtual void readFramebuffer(TextureFormat format, TextureDataType dataType,
                                 uvec2 position, uvec2 size, void* result) const = 0;

    /**
     * @brief Deletes a texture.
     *
     * @param texture The texture to delete.
     */
    virtual void deleteTexture(TextureResource& texure) const = 0;

    /**
     * @brief Creates a new framebuffer.
     *
     * @param size The dimensions of the framebuffer.
     * @param attachments The attachments of the framebuffer.
     */
    virtual Framebuffer createFramebuffer(uvec2 size, std::map<FramebufferAttachment, Ref<TextureResource>>&& attachments) const = 0;

    /**
     * @brief Binds a framebuffer.
     *
     * @param framebuffer The framebuffer to bind.
     */
    virtual void bindFramebuffer(const Ref<Framebuffer>& framebuffer) = 0;

    /**
     * @brief Deletes a framebuffer.
     *
     * @param framebuffer The framebuffer to delete.
     */
    virtual void deleteFramebuffer(Framebuffer& framebuffer) const = 0;

    /**
     * @brief Submits a directional light.
     *
     * @param light The light to submit.
     */
    virtual void submitLight(const RendererDirectionalLight& light) = 0;

    /**
     * @brief Submits a point light.
     *
     * @param light The light to submit.
     */
    virtual void submitLight(const RendererPointLight& light) = 0;

    /**
     * @brief Submits a spot light.
     *
     * @param light The light to submit.
     */
    virtual void submitLight(const RendererSpotLight& light) = 0;

    /*
     * @returns The previous frame GPU time in ms.
     */
    virtual f32 getPreviousFrameGPUTime() const = 0;

    /**
     * @return The current renderer.
     */
    static IRenderer* Instance() {
        return s_renderer.get();
    }

private:
    static inline std::unique_ptr<IRenderer> s_renderer;

    friend Application;
};

}  // namespace labeeri
