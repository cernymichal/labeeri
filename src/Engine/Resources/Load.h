#pragma once

#include "Engine/Resources/MaterialResource.h"
#include "Engine/Resources/ModelResource.h"

namespace labeeri::Engine {

Ref<ShaderResource> loadShader(const std::filesystem::path& path);

Ref<MeshResource> loadMesh(const std::filesystem::path& filePath);

Ref<TextureResource> loadTexture(const std::filesystem::path& filePath, bool gammaCorrected = true);

Ref<TextureResource> loadCubemap(const std::filesystem::path& folderPath, bool gammaCorrected = true);

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

}  // namespace labeeri::Engine
