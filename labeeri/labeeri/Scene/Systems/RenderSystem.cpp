#include "RenderSystem.h"

#include "Renderer/IRenderer.h"
#include "Resources/Resources.h"
#include "Scene/Components/Model.h"
#include "Scene/Components/Transform.h"
#include "Scene/ECS/Instance.h"

namespace labeeri {

static void drawModel(const Ref<ModelResource>& model, const mat4& modelMatrix) {
    auto& shader = model->m_material->m_shader;
    if (!shader)
        shader = Resources<ShaderResource>::Get("shaders/flat");

    LAB_RENDERER->useShaderProgram(shader);
    LAB_RENDERER->bindMesh(model->m_mesh);
    LAB_RENDERER->bindPVM(modelMatrix);
    model->m_material->bindUniforms();

    LAB_RENDERER->drawMesh();
}

ECS::ComponentSignature RenderSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<Model>());
    return signature;
}

void RenderSystem::drawOpaque() const {
    for (Entity entity : entities()) {
        auto& model = entity.getComponent<Model>()->m_ref;
        if (!model->m_material->opaque())
            continue;
        auto transform = entity.getComponent<Transform>();

        drawModel(model, transform->modelMatrix());
    }
}

void RenderSystem::drawTransparent() const {
    for (Entity entity : entities()) {
        auto& model = entity.getComponent<Model>()->m_ref;
        if (model->m_material->opaque())
            continue;
        auto transform = entity.getComponent<Transform>();

        drawModel(model, transform->modelMatrix());
    }
}

void RenderSystem::drawIds() const {
    LAB_RENDERER->useShaderProgram(Resources<ShaderResource>::Get("shaders/id"));

    for (Entity entity : entities()) {
        auto transform = entity.getComponent<Transform>();
        auto& model = entity.getComponent<Model>()->m_ref;

        LAB_RENDERER->bindMesh(model->m_mesh);
        LAB_RENDERER->bindPVM(transform->modelMatrix());
        LAB_RENDERER->bindUniform("u_id", static_cast<EntityId>(entity));
        LAB_RENDERER->drawMesh();
    }
}

}  // namespace labeeri
