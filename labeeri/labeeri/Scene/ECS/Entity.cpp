#include "Entity.h"

#include "Application.h"
#include "Scene/Components/Transform.h"

namespace labeeri {

Entity Entity::Create(const Ref<ECS::Instance>& ecs) {
    Entity entity = ecs->m_entityManager->createEntity();
    entity.addComponent<Transform>(Transform(entity), ecs);

    return entity;
}

void Entity::destroy(const Ref<ECS::Instance>& ecs) {
    if (LAB_CURRENT_SCENE)
        LAB_CURRENT_SCENE->destroyEntity(*this);

    ecs->m_entityManager->destroyEntity(*this);
    ecs->m_componentManager->entityDestroyed(*this);
    ecs->m_systemManager->entityDestroyed(*this);
    m_id = NULL_ENTITY;
}

}  // namespace labeeri
