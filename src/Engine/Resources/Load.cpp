#include "Load.h"

#define STB_IMAGE_IMPLEMENTATION
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <sstream>

#include "Engine/Renderer/IRenderer.h"

namespace labeeri::Engine {

std::string loadShader(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::stringstream contentBuffer;

    if (!file.good()) {
        LAB_LOG("Failed to open file " << path);
        throw std::runtime_error("Failed to open file");
    }

    contentBuffer << file.rdbuf();
    return contentBuffer.str();
}

Ref<ShaderProgram> loadShaderProgram(const char* path) {
    std::vector<std::pair<ShaderType, const char*>> shaders;
    shaders.reserve(3);

    auto vertexPath = std::string(path) + ".vert";
    std::string vertexShaderSource = loadShader(vertexPath);
    shaders.emplace_back(ShaderType::Vertex, vertexShaderSource.c_str());

    auto fragmentPath = std::string(path) + ".frag";
    std::string fragmentShaderSource = loadShader(fragmentPath);
    shaders.emplace_back(ShaderType::Fragment, fragmentShaderSource.c_str());

    auto geometryPath = std::string(path) + ".geom";
    std::string geometryShaderSource;
    if (std::filesystem::exists(geometryPath)) {
        geometryShaderSource = loadShader(geometryPath);
        shaders.emplace_back(ShaderType::Geometry, geometryShaderSource.c_str());
    }

    ShaderProgram program = LAB_RENDERER->createShaderProgram(shaders);

    return makeRef<ShaderProgram>(std::move(program));
}

Ref<Mesh> loadMesh(const char* filePath) {
    LAB_LOGH3("Loading mesh " << filePath);

    Assimp::Importer importer;

    // normalize size
    // importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate                 // Triangulate polygons (if any).
                                                           | aiProcess_PreTransformVertices  // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
                                                           | aiProcess_GenSmoothNormals      // Calculate normals per vertex.
                                                           | aiProcess_CalcTangentSpace      // Calculate tangents per vetex.
                                                           | aiProcess_JoinIdenticalVertices);

    if (scene == nullptr) {
        LAB_LOG("assimp error: " << importer.GetErrorString());
        throw std::runtime_error("assimp error");
    }

    if (scene->mNumMeshes != 1) {
        LAB_LOG("Can only load one mesh at a time");
        throw std::runtime_error("More than one mesh in file");
    }

    const aiMesh* assimpMesh = scene->mMeshes[0];

    uint32_t vertexCount = assimpMesh->mNumVertices;
    uint32_t faceCount = assimpMesh->mNumFaces;
    auto vertices = reinterpret_cast<float*>(assimpMesh->mVertices);
    float* normals = assimpMesh->HasNormals() ? reinterpret_cast<float*>(assimpMesh->mNormals) : nullptr;
    float* tangents = assimpMesh->HasTangentsAndBitangents() ? reinterpret_cast<float*>(assimpMesh->mTangents) : nullptr;

    // UVs
    std::vector<std::vector<float>> UVs;
    if (assimpMesh->HasTextureCoords(0)) {
        UVs.emplace_back();
        UVs[0].reserve((size_t)vertexCount * 2);

        for (size_t i = 0; i < vertexCount; i++) {
            aiVector3D vector = (assimpMesh->mTextureCoords[0])[i];
            UVs[0].push_back(vector.x);
            UVs[0].push_back(vector.y);
        }
    }
    std::vector<const float*> uvPtrs;
    uvPtrs.reserve(UVs.size());
    for (const auto& map : UVs)
        uvPtrs.push_back(map.data());

    // indices
    std::vector<unsigned int> indices;
    indices.reserve((size_t)assimpMesh->mNumFaces * 3);

    for (size_t i = 0; i < assimpMesh->mNumFaces; i++) {
        indices.push_back(assimpMesh->mFaces[i].mIndices[0]);
        indices.push_back(assimpMesh->mFaces[i].mIndices[1]);
        indices.push_back(assimpMesh->mFaces[i].mIndices[2]);
    }

    LAB_LOG("Data loaded");

    Mesh mesh = LAB_RENDERER->createMesh(vertices, vertexCount, normals, tangents, uvPtrs, indices.data(), faceCount);

    return makeRef<Mesh>(std::move(mesh));
}

Ref<Texture> loadTexture(const char* filePath, bool gammaCorrected) {
    LAB_LOGH3("Loading texture " << filePath);

    stbi_set_flip_vertically_on_load(true);

    glm::ivec2 size;
    int channels;
    unsigned char* data = stbi_load(filePath, &size.x, &size.y, &channels, 0);
    if (!data) {
        LAB_LOG("Failed to load texture " << filePath);
        throw std::runtime_error("Failed to load texture");
    }

    TextureFormat format = channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;

    TextureInternalFormat internalFormat;
    if (gammaCorrected)
        internalFormat = channels == 4 ? TextureInternalFormat::SRGBA : TextureInternalFormat::SRGB;
    else
        internalFormat = channels == 4 ? TextureInternalFormat::RGBA : TextureInternalFormat::RGB;

    auto texture = LAB_RENDERER->createTexture(TextureType::Texture2D,
                                               internalFormat, format, TextureDataType::UnsignedByte,
                                               size, data);

    stbi_image_free(data);

    return makeRef<Texture>(std::move(texture));
}

}  // namespace labeeri::Engine
