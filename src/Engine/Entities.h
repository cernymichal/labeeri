#pragma once

#include "Engine/Scene/ECS/Entity.h"
#include "Engine/Scene/Scene.h"

namespace labeeri::Engine {

namespace Entities {

/**
 * @brief TODO
 */
Entity Flycam(Scene& scene, float speed = 4.0, double sensitivity = 0.002);

/**
 * @brief TODO
 */
Entity DirectionalLight(Scene& scene, const glm::vec3& rotation, float intensity = 1.0);

/**
 * @brief TODO
 */
Entity PointLight(Scene& scene, const glm::vec3& position, float intensity = 1.0);

/**
 * @brief TODO
 */
Entity SpotLight(Scene& scene, const glm::vec3& position, const glm::vec3& rotation, float intensity = 1.0);

};  // namespace Entities

}  // namespace labeeri::Engine
