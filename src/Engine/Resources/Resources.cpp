#include "Resources.h"

#include "Engine/Resources/Load.h"

namespace labeeri::Engine {

Ref<ShaderResource> tryFindShader(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_SHADER_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        auto path = entry.path();
        if (!entry.is_directory() && path.stem() == nameStr)
            return Resources<ShaderResource>::Get(path.replace_extension("").string(), false);
    }

    return nullptr;
}

Ref<MeshResource> tryFindMesh(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_MESH_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory() && entry.path().filename() == nameStr)
            return Resources<MeshResource>::Get(entry.path().string(), false);
    }

    return nullptr;
}

Ref<TextureResource> tryFindTexture(const char* name) {
    auto nameStr = std::string(name);
    const std::filesystem::path directory(DEFAULT_TEXTURE_DIRECTORY);

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory() && entry.path().filename() == nameStr)
            return Resources<TextureResource>::Get(entry.path().string(), false);
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory / "cubemaps")) {
        if (entry.is_directory() && entry.path().filename() == nameStr) {
            return loadCubemap(entry.path());
        }
    }

    return nullptr;
}

Ref<MaterialResource> tryFindMaterial(const char* name) {
    auto nameStr = std::string(name);

    if (nameStr == "flatWhite")
        return makeRef<FlatMaterialResource>(Resources<ShaderResource>::Get("flat"), glm::vec3(1.0f));
    if (nameStr == "grey")
        return makeRef<ShadedMaterialResource>(Resources<ShaderResource>::Get("phong"), glm::vec3(0.7f));
    if (nameStr == "UVTest")
        return makeRef<FlatMaterialResource>(Resources<ShaderResource>::Get("flat"), Resources<TextureResource>::Get("uv_test.png"));

    return nullptr;
}

Ref<ModelResource> tryFindModel(const char* name) {
    auto nameStr = std::string(name);

    if (nameStr == "whiteCube")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("cube.obj"));
    if (nameStr == "whiteSphere")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("sphere.obj"));
    if (nameStr == "whiteCone")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("flatWhite"), Resources<MeshResource>::Get("cone.obj"));
    if (nameStr == "basicCube")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("grey"), Resources<MeshResource>::Get("cube.obj"));
    if (nameStr == "basicSphere")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("grey"), Resources<MeshResource>::Get("sphere.obj"));
    if (nameStr == "basicPlane")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("grey"), Resources<MeshResource>::Get("plane.obj"));
    if (nameStr == "basicCone")
        return makeRef<ModelResource>(Resources<MaterialResource>::Get("grey"), Resources<MeshResource>::Get("cone.obj"));

    return nullptr;
}

}  // namespace labeeri::Engine
