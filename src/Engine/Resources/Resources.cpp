#include "Resources.h"

#include "Engine/Resources/Load.h"
#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {
const ShaderProgramRef& Shaders::fallback() {
    static ShaderProgramRef shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/fallback.vert", "resources/engine/shaders/fallback.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const ShaderProgramRef& Shaders::flat() {
    static ShaderProgramRef shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/flat.vert", "resources/engine/shaders/flat.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const ShaderProgramRef& Shaders::phong() {
    static ShaderProgramRef shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/phong.vert", "resources/engine/shaders/phong.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const MeshRef& Meshes::cube() {
    static MeshRef mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/cube.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const MeshRef& Meshes::sphere() {
    static MeshRef mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/sphere.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const TextureRef& Textures::test() {
    static TextureRef texture;

    if (!texture) {
        try {
            texture = loadTexture("resources/engine/textures/uv_test.png");
        }
        catch (const std::exception&) {
        }
    }

    return texture;
}

const std::shared_ptr<FlatMaterial>& Materials::flatGrey() {
    static std::shared_ptr<FlatMaterial> material;

    if (!material && Shaders::flat())
        material = std::make_shared<FlatMaterial>(Shaders::flat(), glm::vec3(0.7f));

    return material;
}

const std::shared_ptr<PhongMaterial>& Materials::grey() {
    static std::shared_ptr<PhongMaterial> material;

    if (!material && Shaders::flat()) {
        material = std::make_shared<PhongMaterial>(Shaders::phong());
        material->m_diffuse = glm::vec3(0.7f);
    }

    return material;
}

const std::shared_ptr<FlatMaterial>& Materials::UVTest() {
    static std::shared_ptr<FlatMaterial> material;

    if (!material && Shaders::flat())
        material = std::make_shared<FlatMaterial>(Shaders::flat(), Textures::test());

    return material;
}

const ModelRef& Models::basicCube() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatGrey(), Meshes::cube());

    return model;
}

const ModelRef& Models::basicSphere() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatGrey(), Meshes::sphere());

    return model;
}

}  // namespace labeeri::Engine
