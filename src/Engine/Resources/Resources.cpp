#include "Resources.h"

#include "Engine/Resources/Load.h"

namespace labeeri::Engine {
const Ref<ShaderProgram>& Shaders::fallback() {
    static Ref<ShaderProgram> shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/fallback.vert", "resources/engine/shaders/fallback.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const Ref<ShaderProgram>& Shaders::flat() {
    static Ref<ShaderProgram> shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/flat.vert", "resources/engine/shaders/flat.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const Ref<ShaderProgram>& Shaders::phong() {
    static Ref<ShaderProgram> shader;

    if (!shader) {
        try {
            shader = loadShaderProgram("resources/engine/shaders/phong.vert", "resources/engine/shaders/phong.frag");
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const Ref<Mesh>& Meshes::cube() {
    static Ref<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/cube.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const Ref<Mesh>& Meshes::sphere() {
    static Ref<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/sphere.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const Ref<Mesh>& Meshes::plane() {
    static Ref<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/plane.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const Ref<Mesh>& Meshes::cone() {
    static Ref<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = loadMesh("resources/engine/models/cone.obj");
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const Ref<Texture>& Textures::test() {
    static Ref<Texture> texture;

    if (!texture) {
        try {
            texture = loadTexture("resources/engine/textures/uv_test.png");
        }
        catch (const std::exception&) {
        }
    }

    return texture;
}

const Ref<FlatMaterial>& Materials::flatWhite() {
    static Ref<FlatMaterial> material;

    if (!material && Shaders::flat())
        material = std::make_shared<FlatMaterial>(Shaders::flat(), glm::vec3(1.0f));

    return material;
}

const Ref<ShadedMaterial>& Materials::grey() {
    static Ref<ShadedMaterial> material;

    if (!material && Shaders::phong()) {
        material = std::make_shared<ShadedMaterial>(Shaders::phong());
        material->m_diffuse = glm::vec3(0.7f);
    }

    return material;
}

const Ref<FlatMaterial>& Materials::UVTest() {
    static Ref<FlatMaterial> material;

    if (!material && Shaders::flat())
        material = std::make_shared<FlatMaterial>(Shaders::flat(), Textures::test());

    return material;
}

const Ref<Model>& Models::whiteCube() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::cube());

    return model;
}

const Ref<Model>& Models::whiteSphere() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::sphere());

    return model;
}

const Ref<Model>& Models::whiteCone() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::flatWhite(), Meshes::cone());

    return model;
}

const Ref<Model>& Models::basicCube() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::cube());

    return model;
}

const Ref<Model>& Models::basicSphere() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::sphere());

    return model;
}

const Ref<Model>& Models::basicPlane() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::plane());

    return model;
}

const Ref<Model>& Models::basicCone() {
    static Ref<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::grey(), Meshes::cone());

    return model;
}

}  // namespace labeeri::Engine
