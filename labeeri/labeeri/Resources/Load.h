#pragma once

#include "Renderer/RendererParameters.h"
#include "Resources/MaterialResource.h"
#include "Resources/ModelResource.h"

namespace labeeri {

inline std::filesystem::path RESOURCES_FOLDER = "./resources/";
inline std::filesystem::path ENGINE_RESOURCES_FOLDER = "./resources/";

inline std::filesystem::path locateResourceFile(const std::filesystem::path& path) {
    auto engineResourcesPath = ENGINE_RESOURCES_FOLDER / path;

    if (std::filesystem::exists(engineResourcesPath))
        return engineResourcesPath;

    auto resourcesPath = RESOURCES_FOLDER / path;
    if (std::filesystem::exists(resourcesPath))
        return resourcesPath;

    if (std::filesystem::exists(path))
        return path;

    return std::filesystem::path();  // empty path
}

/**
 * @brief Load a shader program from a file.
 *
 * @param path The path to the shader file.
 * @return The created shader resource.
 */
Ref<ShaderResource> loadShader(const std::filesystem::path& path);

/**
 * @brief Load a mesh from a file.
 *
 * @param path The path to the mesh file.
 * @return The created mesh resource.
 */
Ref<MeshResource> loadMesh(const std::filesystem::path& filePath);

/**
 * @brief Load a texture from a file.
 *
 * @param filePath The path to the texture file.
 * @param gammaCorrected Whether the texture is already gamma corrected.
 * @param type The type of the texture.
 * @return The created texture resource.
 */
Ref<TextureResource> loadTexture(const std::filesystem::path& filePath, bool gammaCorrected = true, TextureType type = TextureType::Texture2D);

/**
 * @brief Load a cubemap from a folder.
 *
 * @param folderPath The path to the folder containing the cubemap textures.
 * @param gammaCorrected Whether the textures are already gamma corrected.
 * @return The created texture resource.
 */
Ref<TextureResource> loadCubemap(const std::filesystem::path& folderPath, bool gammaCorrected = true);

/**
 * @brief Load a resource from a file.
 *
 * @tparam T The type of the resource.
 * @param path The path to the resource file.
 * @return The created resource.
 */
template <typename T>
static Ref<T> load(const std::filesystem::path& path) {
    throw std::runtime_error("Loading this resource type not supported");
}

template <>
static Ref<ShaderResource> load<ShaderResource>(const std::filesystem::path& path) {
    return loadShader(path);
}

template <>
static Ref<MeshResource> load<MeshResource>(const std::filesystem::path& path) {
    return loadMesh(path);
}

template <>
static Ref<TextureResource> load<TextureResource>(const std::filesystem::path& path) {
    bool gammaCorrected = true;

    const auto filename = path.filename().string();
    if (filename.find("normal") != std::string::npos || filename.find("specular") != std::string::npos || filename.find("_lin.") != std::string::npos)
        gammaCorrected = false;

    return loadTexture(path, gammaCorrected);
}

template <>
static Ref<MaterialResource> load<MaterialResource>(const std::filesystem::path& path) {
    return nullptr;
}

template <>
static Ref<ModelResource> load<ModelResource>(const std::filesystem::path& path) {
    return nullptr;
}

}  // namespace labeeri
