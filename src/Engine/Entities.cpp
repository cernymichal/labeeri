#include "Entities.h"

#include "Engine/Resources/Resources.h"

namespace labeeri::Engine {

Ref<Entity> Entities::Flycam(float speed, double sensitivity) {
    auto entity = Entity::Create();

    entity->m_camera = std::make_shared<Camera>(entity->transform());
    entity->m_movement = std::make_shared<Movement>(entity->transform(), speed);
    entity->m_look = std::make_shared<Look>(entity->transform(), sensitivity);

    return entity;
}

Ref<Entity> Entities::DirectionalLight(const glm::vec3& rotation, float intensity) {
    auto entity = Entity::Create();

    entity->m_model = Models::whiteCube();
    entity->transform()->move(glm::vec3(0, 0.5, 0));
    entity->transform()->rotate(rotation);
    entity->transform()->setScale(glm::vec3(0.1, 0.1, 0.5));
    entity->m_light = std::make_shared<Light>(Light::Directional());
    entity->m_light->m_intensity = intensity;

    return entity;
}

Ref<Entity> Entities::PointLight(const glm::vec3& position, float intensity) {
    auto entity = Entity::Create();

    entity->m_model = Models::whiteSphere();
    entity->transform()->setPosition(position);
    entity->transform()->setScale(glm::vec3(0.3, 0.3, 0.3));
    entity->m_light = std::make_shared<Light>(Light::Point());
    entity->m_light->m_intensity = intensity;

    return entity;
}

EntityPack Entities::SpotLight(const glm::vec3& position, const glm::vec3& rotation, float intensity) {
    auto entity = Entity::Create();
    auto cone = Entity::Create();

    cone->m_model = Models::whiteCone();
    cone->transform()->rotate(glm::vec3(glm::radians(90.0), 0, 0));
    cone->transform()->setScale(glm::vec3(0.3, 0.3, 0.3));
    cone->transform()->setParent(entity->transform());
    entity->transform()->setPosition(position);
    entity->transform()->rotate(rotation);
    entity->m_light = std::make_shared<Light>(Light::Spot());
    entity->m_light->m_intensity = intensity;

    return {entity, cone};
}

}  // namespace labeeri::Engine
