#pragma once

#include "Engine/Resources/Load.h"

namespace labeeri::Engine {

template <typename T>
class Resources {
public:
    static Resources<T>& instance() {
        static Resources<T> instance;
        return instance;
    }

    static const Ref<T>& get(const std::string& name, bool tryFind = true) {
        auto iter = instance().m_resources.find(name);

        if (iter != instance().m_resources.end())
            return iter->second;

        Ref<T> resource;
        if (tryFind)
            resource = tryFindResource<T>(name.c_str());

        if (!resource)
            resource = load<T>(name.c_str());

        instance().m_resources[name] = resource;
        return instance().m_resources[name];
    }

    static Ref<T>& set(const std::string& name) {
        return instance().m_resources[name];
    }

    static void clear() {
        instance().m_resources.clear();
    }

    static void remove(const std::string& name) {
        instance().m_resources.erase(name);
    }

    /*
    static void reloadAll() {
        for (auto& [name, resource] : instance().m_resources)
            *resource = std::move(*load<T, const char*>(name.c_str()));
    }
    */
private:
    std::unordered_map<std::string, Ref<T>> m_resources;
};

Ref<ShaderProgram> tryFindShaderProgram(const char* name);

Ref<Mesh> tryFindMesh(const char* name);

Ref<Texture> tryFindTexture(const char* name);

Ref<Material> tryFindMaterial(const char* name);

Ref<Model> tryFindModel(const char* name);

template <typename T>
static Ref<T> tryFindResource(const char* name) {
    throw std::runtime_error("Finding defautls of this resource type not supported");
}

template <>
static Ref<ShaderProgram> tryFindResource<ShaderProgram>(const char* name) {
    return tryFindShaderProgram(name);
}

template <>
static Ref<Mesh> tryFindResource<Mesh>(const char* name) {
    return tryFindMesh(name);
}

template <>
static Ref<Texture> tryFindResource<Texture>(const char* name) {
    return tryFindTexture(name);
}

template <>
static Ref<Material> tryFindResource<Material>(const char* name) {
    return tryFindMaterial(name);
}

template <>
static Ref<Model> tryFindResource<Model>(const char* name) {
    return tryFindModel(name);
}

}  // namespace labeeri::Engine
