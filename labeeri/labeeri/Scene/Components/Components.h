#pragma once

#include "Scene/Components/Camera.h"
#include "Scene/Components/Collider.h"
#include "Scene/Components/Light.h"
#include "Scene/Components/Model.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/Transform.h"

namespace labeeri {

/**
 * @brief Registers all default components into the ECS system.
 *
 * (Camera, Collider, Light, Model, RigidBody, Transform)
 *
 * @param ecs The ECS instance to register the components into.
 */
static void registerDefaultComponents(const Ref<ECS::Instance>& ecs) {
    ecs->m_componentManager->registerComponent<Camera>();
    ecs->m_componentManager->registerComponent<Collider>();
    ecs->m_componentManager->registerComponent<Light>();
    ecs->m_componentManager->registerComponent<Model>();
    ecs->m_componentManager->registerComponent<RigidBody>();
    ecs->m_componentManager->registerComponent<Transform>();
}

}  // namespace labeeri
