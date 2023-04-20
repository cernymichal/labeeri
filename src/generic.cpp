#include "generic.h"

#include "graphics/load.h"

const std::shared_ptr<ShaderProgram>& Shaders::basic() {
    static std::shared_ptr<ShaderProgram> shader;

    if (!shader) {
        try {
            shader = std::make_shared<ShaderProgram>(loadShaderProgram("resources/engine/shaders/basic.vert", "resources/engine/shaders/basic.frag"));
        }
        catch (const std::exception&) {
        }
    }

    return shader;
}

const std::shared_ptr<Material>& Materials::basic() {
    static std::shared_ptr<Material> material;

    if (!material && Shaders::basic())
        material = std::make_shared<Material>(Shaders::basic());

    return material;
}

const std::shared_ptr<Mesh>& Meshes::cube() {
    static std::shared_ptr<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = std::make_shared<Mesh>(loadMesh("resources/engine/models/cube.obj"));
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const std::shared_ptr<Mesh>& Meshes::sphere() {
    static std::shared_ptr<Mesh> mesh;

    if (!mesh) {
        try {
            mesh = std::make_shared<Mesh>(loadMesh("resources/engine/models/sphere.obj"));
        }
        catch (const std::exception&) {
        }
    }

    return mesh;
}

const std::shared_ptr<Model>& Models::basicCube() {
    static std::shared_ptr<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::basic(), Meshes::cube());

    return model;
}

const std::shared_ptr<Model>& Models::basicSphere() {
    static std::shared_ptr<Model> model;

    if (!model)
        model = std::make_shared<Model>(nullptr, nullptr);

    if (!model->m_material || !model->m_mesh)
        *model = Model(Materials::basic(), Meshes::sphere());

    return model;
}
