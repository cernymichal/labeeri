#include "RenderSystem.h"

#include "Engine/Renderer/IRenderer.h"
#include "Engine/Resources/Resources.h"
#include "Engine/Scene/Components/Light.h"
#include "Engine/Scene/Components/Model.h"
#include "Engine/Scene/Components/Transform.h"
#include "Engine/Scene/ECS/Instance.h"

namespace labeeri::Engine {

void drawModel(const Ref<ModelResource>& model, const glm::mat4& modelMatrix) {
    auto& shader = model->m_material->m_shader;
    if (!shader)
        shader = Resources<ShaderResource>::Get("flat");

    LAB_RENDERER->useShaderProgram(shader);
    LAB_RENDERER->bindMesh(model->m_mesh);
    LAB_RENDERER->bindPVM(modelMatrix);
    model->m_material->bindUniforms();

    LAB_RENDERER->drawMesh();

    LAB_LOG_RENDERAPI_ERROR();
}

ECS::ComponentSignature RenderSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<Model>());
    return signature;
}

void RenderSystem::drawOpaque() {
    for (Entity entity : entities()) {
        auto& model = *entity.getComponent<Model>();
        if (!model->m_material->opaque())
            continue;
        auto& transform = entity.getComponent<Transform>();

        drawModel(model, transform.modelMatrix());
    }
}

void RenderSystem::drawTransparent() {
    for (Entity entity : entities()) {
        auto& model = *entity.getComponent<Model>();
        if (model->m_material->opaque())
            continue;
        auto& transform = entity.getComponent<Transform>();

        drawModel(model, transform.modelMatrix());
    }
}

void RenderSystem::drawIds() {
    LAB_RENDERER->useShaderProgram(Resources<ShaderResource>::Get("id"));

    for (Entity entity : entities()) {
        auto& transform = entity.getComponent<Transform>();
        auto& model = *entity.getComponent<Model>();

        LAB_RENDERER->bindMesh(model->m_mesh);
        LAB_RENDERER->bindPVM(transform.modelMatrix());
        LAB_RENDERER->bindUniform("u_id", static_cast<EntityId>(entity));
        LAB_RENDERER->drawMesh();
    }
}

ECS::ComponentSignature LightSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<Light>());
    return signature;
}

void LightSystem::bindLights() {
    for (Entity entity : entities()) {
        auto& transform = entity.getComponent<Transform>();
        auto& light = entity.getComponent<Light>();

        light.submit(transform);
    }
}

}  // namespace labeeri::Engine
