#include "Entities.h"

#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {

Ref<Entity> Entities::Flycam(float speed, double sensitivity) {
    auto entity = Entity::Create();

    entity->m_camera = makeRef<Camera>(entity->transform());
    entity->m_movement = makeRef<Movement>(entity->transform(), speed);
    entity->m_look = makeRef<Look>(entity->transform(), sensitivity);

    return entity;
}

Ref<Entity> Entities::DirectionalLight(const glm::vec3& rotation, float intensity) {
    auto entity = Entity::Create();

    entity->m_model = Resources<Model>::get("whiteCube");
    entity->transform()->move(glm::vec3(0, 0.5, 0));
    entity->transform()->rotate(rotation);
    entity->transform()->setScale(glm::vec3(0.1, 0.1, 0.5));
    entity->m_light = makeRef<Light>(Light::Directional());
    entity->m_light->m_intensity = intensity;

    return entity;
}

Ref<Entity> Entities::PointLight(const glm::vec3& position, float intensity) {
    auto entity = Entity::Create();

    entity->m_model = Resources<Model>::get("whiteSphere");
    entity->transform()->setPosition(position);
    entity->transform()->setScale(glm::vec3(0.3, 0.3, 0.3));
    entity->m_light = makeRef<Light>(Light::Point());
    entity->m_light->m_intensity = intensity;

    return entity;
}

EntityPack Entities::SpotLight(const glm::vec3& position, const glm::vec3& rotation, float intensity) {
    auto entity = Entity::Create();
    auto cone = Entity::Create();

    cone->m_model = Resources<Model>::get("whiteCone");
    cone->transform()->rotate(glm::vec3(glm::radians(90.0), 0, 0));
    cone->transform()->setScale(glm::vec3(0.3, 0.3, 0.3));
    cone->transform()->setParent(entity->transform());
    entity->transform()->setPosition(position);
    entity->transform()->rotate(rotation);
    entity->m_light = makeRef<Light>(Light::Spot());
    entity->m_light->m_intensity = intensity;

    return {entity, cone};
}

}  // namespace labeeri::Engine
