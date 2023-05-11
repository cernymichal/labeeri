#pragma once

#include "Engine/Resources/Material.h"
#include "Engine/Resources/Model.h"

namespace labeeri::Engine {

Ref<ShaderProgram> loadShaderProgram(const char* path);

Ref<Mesh> loadMesh(const char* filePath);

Ref<Texture> loadTexture(const char* filePath);

template <typename T>
static Ref<T> load(const char* path) {
    throw std::runtime_error("Loading this resource type not supported");
}

template <>
static Ref<ShaderProgram> load<ShaderProgram>(const char* path) {
    return loadShaderProgram(path);
}

template <>
static Ref<Mesh> load<Mesh>(const char* path) {
    return loadMesh(path);
}

template <>
static Ref<Texture> load<Texture>(const char* path) {
    return loadTexture(path);
}

template <>
static Ref<Material> load<Material>(const char* path) {
    return std::shared_ptr<Material>(nullptr);
}

template <>
static Ref<Model> load<Model>(const char* path) {
    return std::shared_ptr<Model>(nullptr);
}

}  // namespace labeeri::Engine
