#include "Load.h"

#define STB_IMAGE_IMPLEMENTATION
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <fstream>
#include <sstream>

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {

std::string loadShader(const char* path) {
    std::ifstream file(path);
    std::stringstream contentBuffer;

    if (!file.good()) {
        LAB_LOG("Failed to open file " << path);
        throw std::runtime_error("Failed to open file");
    }

    contentBuffer << file.rdbuf();
    return contentBuffer.str();
}

ShaderProgramRef loadShaderProgram(const char* vertexPath, const char* fragmentPath) {
    LAB_LOGH3("Loading shader program from " << vertexPath << " and " << fragmentPath);

    std::string vertexShaderSource = loadShader(vertexPath);
    std::string fragmentShaderSource = loadShader(fragmentPath);

    ShaderProgram program = LAB_RENDERER->createShaderProgram({{ShaderType::Vertex, vertexShaderSource.c_str()}, {ShaderType::Fragment, fragmentShaderSource.c_str()}});

    return std::make_shared<ShaderProgram>(std::move(program));
}

MeshRef loadMesh(const char* filePath) {
    LAB_LOGH3("Loading mesh " << filePath);

    Assimp::Importer importer;

    // normalize size
    // importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate                 // Triangulate polygons (if any).
                                                           | aiProcess_PreTransformVertices  // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
                                                           | aiProcess_GenSmoothNormals      // Calculate normals per vertex.
                                                           | aiProcess_JoinIdenticalVertices);

    if (scene == NULL) {
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
    float* vertices = reinterpret_cast<float*>(assimpMesh->mVertices);
    float* normals = assimpMesh->HasNormals() ? reinterpret_cast<float*>(assimpMesh->mNormals) : nullptr;

    // UVs
    std::vector<std::vector<float>> UVs;
    if (assimpMesh->HasTextureCoords(0)) {
        UVs.push_back({});
        UVs[0].reserve((size_t)vertexCount * 2);

        for (size_t i = 0; i < vertexCount; i++) {
            aiVector3D vector = (assimpMesh->mTextureCoords[0])[i];
            UVs[0].push_back(vector.x);
            UVs[0].push_back(vector.y);
        }
    }
    std::vector<const float*> UVPtrs;
    for (const auto& map : UVs)
        UVPtrs.push_back(&map[0]);

    // indices
    std::vector<unsigned int> indices;
    indices.reserve((size_t)assimpMesh->mNumFaces * 3);

    for (size_t i = 0; i < assimpMesh->mNumFaces; i++) {
        indices.push_back(assimpMesh->mFaces[i].mIndices[0]);
        indices.push_back(assimpMesh->mFaces[i].mIndices[1]);
        indices.push_back(assimpMesh->mFaces[i].mIndices[2]);
    }

    LAB_LOG("Data loaded");

    Mesh mesh = LAB_RENDERER->createMesh(vertices, vertexCount, normals, UVPtrs, &indices[0], faceCount);

    return std::make_shared<Mesh>(std::move(mesh));
}

TextureRef loadTexture(const char* filePath) {
    LAB_LOGH3("Loading texture " << filePath);

    stbi_set_flip_vertically_on_load(true);

    glm::ivec2 size;
    int channels;
    unsigned char* data = stbi_load(filePath, &size.x, &size.y, &channels, 0);
    if (!data) {
        LAB_LOG("Failed to load texture " << filePath);
        throw std::runtime_error("Failed to load texture");
    }

    Texture texture = LAB_RENDERER->createTexture(TextureType::Texture2D, channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB, data, size);

    stbi_image_free(data);

    return std::make_shared<Texture>(std::move(texture));
}

}  // namespace labeeri::Engine
