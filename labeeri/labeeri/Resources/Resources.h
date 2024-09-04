#pragma once

#include "Resources/Load.h"

namespace labeeri {

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

        resource = load<T>(name);

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
    static void ReloadAll() {
        for (auto& [name, resource] : Instance().m_resources)
            *resource = std::move(*load<T, const char*>(name.c_str()));
    }
    */

private:
    std::unordered_map<std::string, Ref<T>> m_resources;
};

}  // namespace labeeri
