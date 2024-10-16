#include "Entities.h"

#include "Application.h"
#include "Entities.h"
#include "Resources/Resources.h"
#include "Resources/Scripts/FlycamController.h"
#include "Resources/Scripts/PlayerController.h"
#include "Scene/Components/Components.h"

namespace labeeri {

Entity Entities::Flycam(const Ref<Scene>& scene, vec3 position, quat rotation, f32 speed, f64 sensitivity) {
    auto entity = Entity::Create(scene->ecs());

    auto transform = entity.getComponent<Transform>(scene->ecs());
    transform->setPosition(position);
    transform->setRotation(rotation);

    entity.addComponent<Camera>(Camera(true), scene->ecs());
    entity.addComponent<RigidBody>(RigidBody(), scene->ecs());
    entity.addComponent<Collider>(Collider::AABB(vec3(0.16f)), scene->ecs());
    scene->addScript<FlycamController>(entity, speed, sensitivity);

    return entity;
}

Entity Entities::Player(const Ref<Scene>& scene, vec3 position, quat rotation, f32 speed, f64 sensitivity, f32 height) {
    auto entity = Entity::Create(scene->ecs());

    auto transform = entity.getComponent<Transform>(scene->ecs());
    transform->setPosition(VEC_UP * height);
    transform->move(position);
    transform->setRotation(rotation);

    entity.addComponent<Camera>(Camera(true), scene->ecs());
    entity.addComponent<RigidBody>(RigidBody(), scene->ecs());
    entity.addComponent<Collider>(Collider::AABB(vec3(0.16f, height / 2, 0.16f), -VEC_UP * (height / 2)), scene->ecs());
    scene->addScript<PlayerController>(entity, speed, sensitivity);

    return entity;
}

Entity Entities::ColliderCube(const Ref<Scene>& scene, vec3 position, vec3 size) {
    auto entity = Entity::Create(scene->ecs());

    entity.getComponent<Transform>(scene->ecs())->setPosition(position);
    entity.addComponent<RigidBody>(RigidBody::Static(), scene->ecs());
    entity.addComponent<Collider>(Collider::AABB(size / 2.0f), scene->ecs());

    return entity;
}

Entity Entities::DirectionalLight(const Ref<Scene>& scene, const vec3& rotation, f32 intensity) {
    auto entity = Entity::Create(scene->ecs());

    auto transform = entity.getComponent<Transform>(scene->ecs());
    transform->move(vec3(0, 0.5, 0));
    transform->rotate(rotation);
    transform->setScale(vec3(0.1, 0.1, 0.5));

    auto light = entity.addComponent<Light>(Light::Directional(), scene->ecs());
    light->m_intensity = intensity;

    entity.addComponent<Model>(Model(Resources<ModelResource>::Get("whiteCube")), scene->ecs());

    return entity;
}

Entity Entities::PointLight(const Ref<Scene>& scene, const vec3& position, f32 intensity) {
    auto entity = Entity::Create(scene->ecs());

    auto transform = entity.getComponent<Transform>(scene->ecs());
    transform->setPosition(position);
    transform->setScale(vec3(0.3, 0.3, 0.3));

    auto light = entity.addComponent<Light>(Light::Point(), scene->ecs());
    light->m_intensity = intensity;

    entity.addComponent<Model>(Model(Resources<ModelResource>::Get("whiteSphere")), scene->ecs());

    return entity;
}

Entity Entities::SpotLight(const Ref<Scene>& scene, const vec3& position, const vec3& rotation, f32 intensity) {
    auto entity = Entity::Create(scene->ecs());

    auto transform = entity.getComponent<Transform>(scene->ecs());
    transform->setPosition(position);
    transform->rotate(rotation);
    transform->setScale(vec3(0.3, 0.3, 0.3));

    auto light = entity.addComponent<Light>(Light::Spot(), scene->ecs());
    light->m_intensity = intensity;

    entity.addComponent<Model>(Model(Resources<ModelResource>::Get("whiteCone")), scene->ecs());

    return entity;
}

}  // namespace labeeri
