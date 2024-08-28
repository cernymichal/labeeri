#include "CameraSystem.h"

#include "Scene/Components/Camera.h"

namespace labeeri {

ECS::ComponentSignature CameraSystem::signature(const ECS::Instance& ecs) const {
    ECS::ComponentSignature signature;
    signature.set(ecs.m_componentManager->getComponentType<Camera>());
    signature.set(ecs.m_componentManager->getComponentType<Transform>());
    return signature;
}

}  // namespace labeeri
