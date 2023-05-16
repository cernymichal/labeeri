#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

Ref<ShaderProgram> loadShaderProgram(const std::filesystem::path& path);

Ref<Mesh> loadMesh(const std::filesystem::path& filePath);

Ref<Texture> loadTexture(const std::filesystem::path& filePath, bool gammaCorrected = true);

Ref<Texture> loadCubemap(const std::filesystem::path& folderPath, bool gammaCorrected = true);

template <typename T>
static Ref<T> load(const std::filesystem::path& path) {
    throw std::runtime_error("Loading this resource type not supported");
}

template <>
static Ref<ShaderProgram> load<ShaderProgram>(const std::filesystem::path& path) {
    return loadShaderProgram(path);
}

template <>
static Ref<Mesh> load<Mesh>(const std::filesystem::path& path) {
    return loadMesh(path);
}

template <>
static Ref<Texture> load<Texture>(const std::filesystem::path& path) {
    bool gammaCorrected = true;

    const auto filename = path.filename().string();
    if (filename.find("normal") != std::string::npos || filename.find("specular") != std::string::npos || filename.find("_lin.") != std::string::npos)
        gammaCorrected = false;

    return loadTexture(path, gammaCorrected);
}

template <>
static Ref<Material> load<Material>(const std::filesystem::path& path) {
    return nullptr;
}

template <>
static Ref<Model> load<Model>(const std::filesystem::path& path) {
    return nullptr;
}

}  // namespace labeeri::Engine
