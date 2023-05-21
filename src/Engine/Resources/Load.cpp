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

static std::string loadSingleShader(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::stringstream contentBuffer;

    if (!file.good()) {
        LAB_LOG("Failed to open file " << path);
        throw std::runtime_error("Failed to open file");
    }

    contentBuffer << file.rdbuf();
    return contentBuffer.str();
}

Ref<ShaderResource> loadShader(const std::filesystem::path& path) {
    LAB_LOGH3("Loading shader program " << path);
    std::vector<std::pair<ShaderType, const char*>> shaders;
    shaders.reserve(3);

    auto vertexPath = path.string() + ".vert";
    std::string vertexShaderSource = loadSingleShader(vertexPath);
    shaders.emplace_back(ShaderType::Vertex, vertexShaderSource.c_str());

    auto fragmentPath = path.string() + ".frag";
    std::string fragmentShaderSource = loadSingleShader(fragmentPath);
    shaders.emplace_back(ShaderType::Fragment, fragmentShaderSource.c_str());

    auto geometryPath = path.string() + ".geom";
    std::string geometryShaderSource;
    if (std::filesystem::exists(geometryPath)) {
        geometryShaderSource = loadSingleShader(geometryPath);
        shaders.emplace_back(ShaderType::Geometry, geometryShaderSource.c_str());
    }

    ShaderResource program = LAB_RENDERER->createShaderProgram(shaders);

    return makeRef<ShaderResource>(std::move(program));
}

Ref<MeshResource> loadMesh(const std::filesystem::path& filePath) {
    LAB_LOGH3("Loading mesh " << filePath);

    Assimp::Importer importer;

    // normalize size
    // importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    const aiScene* scene = importer.ReadFile(filePath.string(), aiProcess_Triangulate                 // Triangulate polygons (if any).
                                                                    | aiProcess_PreTransformVertices  // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
                                                                    | aiProcess_GenSmoothNormals      // Calculate normals per vertex.
                                                                    | aiProcess_CalcTangentSpace      // Calculate tangents per vertex.
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

    MeshResource mesh = LAB_RENDERER->createMesh(vertices, vertexCount, normals, tangents, uvPtrs, indices.data(), faceCount);

    return makeRef<MeshResource>(std::move(mesh));
}

struct STBImageResource : ImageResource {
    STBImageResource(const std::filesystem::path& filePath, bool gammaCorrected, bool flip = true) {
        LAB_LOGH3("Loading image " << filePath);

        if (flip)
            stbi_set_flip_vertically_on_load(true);
        else
            stbi_set_flip_vertically_on_load(false);

        int channels;
        glm::ivec2 sizeInt;

        const auto filePathStr = filePath.string();
        if (stbi_is_hdr(filePathStr.c_str())) {
            data = stbi_loadf(filePathStr.c_str(), &sizeInt.x, &sizeInt.y, &channels, 0);
            dataType = TextureDataType::Float32;
            internalFormat = channels == 4 ? TextureInternalFormat::RGBAFloat32 : TextureInternalFormat::RGBFloat32;
            gammaCorrected = false;
        }
        else {
            data = stbi_load(filePathStr.c_str(), &sizeInt.x, &sizeInt.y, &channels, 0);
            dataType = TextureDataType::UByte;
            if (gammaCorrected)
                internalFormat = channels == 4 ? TextureInternalFormat::SRGBA : TextureInternalFormat::SRGB;
            else
                internalFormat = channels == 4 ? TextureInternalFormat::RGBA : TextureInternalFormat::RGB;
        }

        if (!data) {
            LAB_LOG("Failed to load texture " << filePath);
            throw std::runtime_error("Failed to load texture");
        }

        size = sizeInt;
        format = channels == 4 ? TextureFormat::RGBA : TextureFormat::RGB;
    }

    virtual ~STBImageResource() override {
        stbi_image_free(data);
    }
};

Ref<TextureResource> loadTexture(const std::filesystem::path& filePath, bool gammaCorrected) {
    STBImageResource image(filePath, gammaCorrected);
    auto texture = LAB_RENDERER->createTexture(TextureType::Texture2D, image);

    return makeRef<TextureResource>(std::move(texture));
}

Ref<TextureResource> loadCubemap(const std::filesystem::path& path, bool gammaCorrected) {
    std::array<Scoped<ImageResource>, 6> images;

    std::string extension;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_directory() && entry.path().stem() == "px") {
            extension = entry.path().extension().string();
            break;
        }
    }

    images[0] = makeScoped<STBImageResource>((path / ("px" + extension)), gammaCorrected, false);
    images[1] = makeScoped<STBImageResource>((path / ("nx" + extension)), gammaCorrected, false);
    images[2] = makeScoped<STBImageResource>((path / ("py" + extension)), gammaCorrected, false);
    images[3] = makeScoped<STBImageResource>((path / ("ny" + extension)), gammaCorrected, false);
    images[4] = makeScoped<STBImageResource>((path / ("pz" + extension)), gammaCorrected, false);
    images[5] = makeScoped<STBImageResource>((path / ("nz" + extension)), gammaCorrected, false);

    auto texture = LAB_RENDERER->createCubemap(images);

    return makeRef<TextureResource>(std::move(texture));
}

}  // namespace labeeri::Engine
