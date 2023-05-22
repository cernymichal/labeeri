#include "PhysicsSystem.h"

#include "Engine/Scene/Components/Collider.h"
#include "Engine/Scene/Components/RigidBody.h"
#include "Engine/Scene/Components/Transform.h"
#include "Engine/Scene/ECS/Entity.h"

namespace labeeri::Engine {

static bool collistionCheckAABB(const Transform* transfromA, const Collider* colliderA, const Transform* transfromB, const Collider* colliderB) {
    vec3 minA = transfromA->worldPosition() + colliderA->m_center - colliderA->m_extents * transfromA->scale();
    vec3 maxA = transfromA->worldPosition() + colliderA->m_center + colliderA->m_extents * transfromA->scale();
    vec3 minB = transfromB->worldPosition() + colliderB->m_center - colliderB->m_extents * transfromB->scale();
    vec3 maxB = transfromB->worldPosition() + colliderB->m_center + colliderB->m_extents * transfromB->scale();

    return glm::all(glm::lessThanEqual(minA, maxB)) && glm::all(glm::greaterThanEqual(maxA, minB));
}

ECS::ComponentSignature PhysicsSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    signature.set(ecs.m_componentManager->getComponentType<RigidBody>());
    signature.set(ecs.m_componentManager->getComponentType<Collider>());
    return signature;
}

void PhysicsSystem::update(double deltaTime) {
    for (Entity entity : entities()) {
        auto rigidBody = entity.getComponent<RigidBody>();
        if (rigidBody->m_static)
            continue;

        auto transform = entity.getComponent<Transform>();
        auto collider = entity.getComponent<Collider>();

        rigidBody->m_velocity += rigidBody->m_acceleration * static_cast<float>(deltaTime);
        auto delta = rigidBody->m_velocity * static_cast<float>(deltaTime);
        transform->moveWorld(delta);

        if (collides(entity))
            transform->moveWorld(-delta);
    }
}

bool PhysicsSystem::collides(Entity entity) const {
    auto transformA = entity.getComponent<Transform>();
    auto colliderA = entity.getComponent<Collider>();

    if (!colliderA->m_enabled)
        return false;

    for (Entity entityB : entities()) {
        if (entity == entityB)
            continue;

        auto transformB = entityB.getComponent<Transform>();
        auto colliderB = entityB.getComponent<Collider>();

        if (!colliderB->m_enabled)
            continue;

        if (colliderA->m_type != ColliderType::AABB || colliderB->m_type != ColliderType::AABB) {
            LAB_LOG("Collision checking for other types than AABB not implemented!");
            continue;
        }

        if (collistionCheckAABB(transformA, colliderA, transformB, colliderB))
            return true;
    }

    return false;
}

}  // namespace labeeri::Engine
