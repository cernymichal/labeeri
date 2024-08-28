#include "LightSystem.h"

#include "Renderer/IRenderer.h"
#include "Scene/Components/Light.h"
#include "Scene/Components/Transform.h"
#include "Scene/ECS/Instance.h"

namespace labeeri {

static void submitLight(const Light* light, const Transform* transform) {
    switch (light->m_type) {
        case LightType::Directional:
            LAB_RENDERER->submitLight(RendererDirectionalLight(transform->forward(), light->scaledProperties()));
            break;
        case LightType::Point:
            LAB_RENDERER->submitLight(RendererPointLight(transform->position(), light->scaledProperties(), light->m_attenuation));
            break;
        case LightType::Spot:
            LAB_RENDERER->submitLight(RendererSpotLight(transform->position(), transform->forward(), light->m_innerCutoff, light->m_outerCutoff, light->scaledProperties(), light->m_attenuation));
            break;
        default:
            LAB_LOG("Unknown light type");
    }
}

ECS::ComponentSignature LightSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<Light>());
    return signature;
}

void LightSystem::bindLights() const {
    for (Entity entity : entities()) {
        auto transform = entity.getComponent<Transform>();
        auto light = entity.getComponent<Light>();

        submitLight(light, transform);
    }
}

}  // namespace labeeri
