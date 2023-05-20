#include "PhysicsSystem.h"

#include "Engine/Scene/Components/RigidBody.h"
#include "Engine/Scene/Components/Transform.h"
#include "Engine/Scene/ECS/Instance.h"

namespace labeeri::Engine {

ECS::ComponentSignature PhysicsSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<RigidBody>());
    return signature;
}

void PhysicsSystem::update(double deltaTime) {
    for (Entity entity : entities()) {
        auto transform = entity.getComponent<Transform>();
        auto rigidBody = entity.getComponent<RigidBody>();

        rigidBody->m_velocity += rigidBody->m_acceleration * static_cast<float>(deltaTime);
        transform->move(rigidBody->m_velocity * static_cast<float>(deltaTime));
    }
}

}  // namespace labeeri::Engine