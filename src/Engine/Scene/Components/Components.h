#pragma once

#include "Engine/Scene/Components/Camera.h"
#include "Engine/Scene/Components/Collider.h"
#include "Engine/Scene/Components/Light.h"
#include "Engine/Scene/Components/Model.h"
#include "Engine/Scene/Components/RigidBody.h"
#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
static void registerDefaultComponents(const Ref<ECS::Instance>& ecs) {
    ecs->m_componentManager->registerComponent<Camera>();
    ecs->m_componentManager->registerComponent<Collider>();
    ecs->m_componentManager->registerComponent<Light>();
    ecs->m_componentManager->registerComponent<Model>();
    ecs->m_componentManager->registerComponent<RigidBody>();
    ecs->m_componentManager->registerComponent<Transform>();
}

}  // namespace labeeri::Engine
