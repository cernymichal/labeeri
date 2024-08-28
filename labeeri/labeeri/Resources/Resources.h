#pragma once

#include "Resources/Load.h"

namespace labeeri {

/*
 * @brief Try to find a shader resource in the default location.
 *
 * @param name The name of the shader resource.
 * @return The shader resource if found, otherwise nullptr.
 */
Ref<ShaderResource> tryFindShader(const char* name);

/*
 * @brief Try to find a mesh resource in the default location.
 *
 * @param name The name of the mesh resource.
 * @return The mesh resource if found, otherwise nullptr.
 */
Ref<MeshResource> tryFindMesh(const char* name);

/*
 * @brief Try to find a texture resource in the default location.
 *
 * @param name The name of the texture resource.
 * @return The texture resource if found, otherwise nullptr.
 */
Ref<TextureResource> tryFindTexture(const char* name);

/*
 * @brief Try to find a default material resource.
 *
 * @param name The name of the material resource.
 * @return The material resource if found, otherwise nullptr.
 */
Ref<MaterialResource> tryFindMaterial(const char* name);

/*
 * @brief Try to find a default model resource.
 *
 *  @param name The name of the model resource.
 *  @return The model resource if found, otherwise nullptr.
 */
Ref<ModelResource> tryFindModel(const char* name);

/*
 * @brief Try to find a default resource.
 *
 * @tparam T The type of the resource.
 * @param name The name of the resource.
 * @return The resource if found, otherwise nullptr.
 * */

template <typename T>
static Ref<T> tryFindResource(const char* name) {
    throw std::runtime_error("Finding defautls of this resource type not supported");
}

template <>
static Ref<ShaderResource> tryFindResource<ShaderResource>(const char* name) {
    return tryFindShader(name);
}

template <>
static Ref<MeshResource> tryFindResource<MeshResource>(const char* name) {
    return tryFindMesh(name);
}

template <>
static Ref<TextureResource> tryFindResource<TextureResource>(const char* name) {
    return tryFindTexture(name);
}

template <>
static Ref<MaterialResource> tryFindResource<MaterialResource>(const char* name) {
    return tryFindMaterial(name);
}

template <>
static Ref<ModelResource> tryFindResource<ModelResource>(const char* name) {
    return tryFindModel(name);
}

/*
 * @brief Resource manager holding all of the shared objects.
 *
 * @tparam T The type of the resources.
 */
template <typename T>
class Resources {
public:
    /*
     * @return The instance of the resource manager.
     */
    static Resources<T>& Instance() {
        static Resources<T> instance;
        return instance;
    }

    /*
     * @brief Get a resource by name.
     *
     * @param name The name of the resource.
     * @param tryFind Whether to try to find the resource in the default location.
     * @return The resource.
     */
    static const Ref<T>& Get(const std::string& name, bool tryFind = true) {
        auto iter = Instance().m_resources.find(name);

        if (iter != Instance().m_resources.end())
            return iter->second;

        Ref<T> resource;
        if (tryFind)
            resource = tryFindResource<T>(name.c_str());

        if (!resource)
            resource = load<T>(name.c_str());

        return Instance().m_resources[name] = resource;
    }

    /*
     * @brief Return a reference to a resource by name.
     *
     * @param name The name of the resource.
     */
    static Ref<T>& Set(const std::string& name) {
        return Instance().m_resources[name];
    }

    /*
     * @brief Clear all resources.
     */
    static void Clear() {
        Instance().m_resources.clear();
    }

    /*
     * @brief Remove a resource by name.
     *
     * @param name The name of the resource.
     */
    static void Remove(const std::string& name) {
        Instance().m_resources.erase(name);
    }

    /*
    static void reloadAll() {
        for (auto& [name, resource] : Instance().m_resources)
            *resource = std::move(*load<T, const char*>(name.c_str()));
    }
    */

private:
    std::unordered_map<std::string, Ref<T>> m_resources;
};

}  // namespace labeeri
