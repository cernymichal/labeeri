#pragma once

#include "Engine/Resources/Load.h"

namespace labeeri::Engine {

Ref<ShaderResource> tryFindShader(const char* name);

Ref<MeshResource> tryFindMesh(const char* name);

Ref<TextureResource> tryFindTexture(const char* name);

Ref<MaterialResource> tryFindMaterial(const char* name);

Ref<ModelResource> tryFindModel(const char* name);

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

template <typename T>
class Resources {
public:
    static Resources<T>& Instance() {
        static Resources<T> instance;
        return instance;
    }

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

    static Ref<T>& Set(const std::string& name) {
        return Instance().m_resources[name];
    }

    static void Clear() {
        Instance().m_resources.clear();
    }

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

}  // namespace labeeri::Engine
