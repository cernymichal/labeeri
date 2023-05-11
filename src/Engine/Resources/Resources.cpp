#include "Resources.h"

#include <filesystem>

#include "Engine/Resources/Load.h"

namespace labeeri::Engine {

Ref<ShaderProgram> tryFindShaderProgram(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_SHADER_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        auto path = entry.path();
        if (!entry.is_directory() && path.stem() == nameStr)
            return Resources<ShaderProgram>::get(path.replace_extension("").string());
    }

    return nullptr;
}

Ref<Mesh> tryFindMesh(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_MESH_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory() && entry.path().filename() == nameStr)
            return Resources<Mesh>::get(entry.path().string());
    }

    return nullptr;
}

Ref<Texture> tryFindTexture(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_TEXTURE_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory() && entry.path().filename() == nameStr)
            return Resources<Texture>::get(entry.path().string());
    }

    return nullptr;
}

Ref<Material> tryFindMaterial(const char* name) {
    auto nameStr = std::string(name);

    if (nameStr == "flatWhite")
        return std::make_shared<FlatMaterial>(Resources<ShaderProgram>::get("flat"), glm::vec3(1.0f));
    if (nameStr == "grey")
        return std::make_shared<ShadedMaterial>(Resources<ShaderProgram>::get("phong"), glm::vec3(0.7f));
    if (nameStr == "UVTest")
        return std::make_shared<FlatMaterial>(Resources<ShaderProgram>::get("flat"), Resources<Texture>::get("uv_test.png"));

    return nullptr;
}

Ref<Model> tryFindModel(const char* name) {
    auto nameStr = std::string(name);

    if (nameStr == "whiteCube")
        return std::make_shared<Model>(Resources<Material>::get("flatWhite"), Resources<Mesh>::get("cube.obj"));
    if (nameStr == "whiteSphere")
        return std::make_shared<Model>(Resources<Material>::get("flatWhite"), Resources<Mesh>::get("sphere.obj"));
    if (nameStr == "whiteCone")
        return std::make_shared<Model>(Resources<Material>::get("flatWhite"), Resources<Mesh>::get("cone.obj"));
    if (nameStr == "basicCube")
        return std::make_shared<Model>(Resources<Material>::get("grey"), Resources<Mesh>::get("cube.obj"));
    if (nameStr == "basicSphere")
        return std::make_shared<Model>(Resources<Material>::get("grey"), Resources<Mesh>::get("sphere.obj"));
    if (nameStr == "basicPlane")
        return std::make_shared<Model>(Resources<Material>::get("grey"), Resources<Mesh>::get("plane.obj"));
    if (nameStr == "basicCone")
        return std::make_shared<Model>(Resources<Material>::get("grey"), Resources<Mesh>::get("cone.obj"));

    return nullptr;
}

}  // namespace labeeri::Engine
