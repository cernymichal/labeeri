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

const MeshRef& Meshes::plane() {
    static MeshRef mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/plane.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const MeshRef& Meshes::cone() {
    static MeshRef mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/cone.obj");
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

const std::shared_ptr<FlatMaterial>& Materials::flatWhite() {
    static std::shared_ptr<FlatMaterial> material;

    if (!material && Shaders::flat())
        material = std::make_shared<FlatMaterial>(Shaders::flat(), glm::vec3(1.0f));

    return material;
}

const std::shared_ptr<ShadedMaterial>& Materials::grey() {
    static std::shared_ptr<ShadedMaterial> material;

    if (!material && Shaders::phong()) {
        material = std::make_shared<ShadedMaterial>(Shaders::phong());
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

const ModelRef& Models::whiteCube() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::cube());

    return model;
}

const ModelRef& Models::whiteSphere() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::sphere());

    return model;
}

const ModelRef& Models::whiteCone() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::cone());

    return model;
}

const ModelRef& Models::basicCube() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::cube());

    return model;
}

const ModelRef& Models::basicSphere() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::sphere());

    return model;
}

const ModelRef& Models::basicPlane() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::plane());

    return model;
}

const ModelRef& Models::basicCone() {
    static ModelRef model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::cone());

    return model;
}

}  // namespace labeeri::Engine
