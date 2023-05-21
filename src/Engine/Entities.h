#pragma once

#include "Engine/Scene/ECS/Entity.h"
#include "Engine/Scene/Scene.h"

namespace labeeri::Engine {

namespace Entities {

/**
 * @brief TODO
 */
Entity Flycam(const Ref<Scene>& scene, float speed = 4.0, double sensitivity = 0.002);

/**
 * @brief TODO
 */
Entity Player(const Ref<Scene>& scene, float speed = 4.0, double sensitivity = 0.002, float height = 1.75f);

/**
 * @brief TODO
 */
Entity ColliderCube(const Ref<Scene>& scene, vec3 position, vec3 size);

/**
 * @brief TODO
 */
Entity DirectionalLight(const Ref<Scene>& scene, const vec3& rotation, float intensity = 1.0);

/**
 * @brief TODO
 */
Entity PointLight(const Ref<Scene>& scene, const vec3& position, float intensity = 1.0);

/**
 * @brief TODO
 */
Entity SpotLight(const Ref<Scene>& scene, const vec3& position, const vec3& rotation, float intensity = 1.0);

};  // namespace Entities

}  // namespace labeeri::Engine
