#pragma once

#include "Entity.h"

#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

Entity Entity::Create(const ECS::Instance& ecs) {
    Entity entity = ecs.m_entityManager->createEntity();
    entity.addComponent<Transform>(Transform(entity), ecs);

    return entity;
}

}  // namespace labeeri::Engine
