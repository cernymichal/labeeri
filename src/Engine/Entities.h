#pragma once

#include "Engine/Scene/ECS/Entity.h"
#include "Engine/Scene/Scene.h"

namespace labeeri::Engine {

namespace Entities {

/**
 * @brief Creates a new entity with the FlycamController script.
 *
 * @param scene The scene to create the entity in.
 * @param position The position of the flycam.
 * @param rotation The rotation of the flycam.
 * @param speed The speed of the flycam.
 * @param sensitivity The mouse sensitivity of the camera.
 * @return The created entity.
 */
Entity Flycam(const Ref<Scene>& scene, vec3 position = vec3(0.0f), quat rotation = quat(), float speed = 3.0f, double sensitivity = 0.002);

/**
 * @brief Creates a new entity with the PlayerController script.
 *
 * @param scene The scene to create the entity in.
 * @param position The position of the player.
 * @param rotation The rotation of the player.
 * @param speed The speed of the player.
 * @param sensitivity The mouse sensitivity of the camera.
 * @param height The height of the player.
 * @return The created entity.
 */
Entity Player(const Ref<Scene>& scene, vec3 position = vec3(0.0f), quat rotation = quat(), float speed = 3.0f, double sensitivity = 0.002, float height = 1.75f);

/**
 * @brief Creates a new entity with a RigidBody and AABB collider component.
 *
 * @param scene The scene to create the entity in.
 * @param position The position of the entity.
 * @param size The size of the collider.
 * @return The created entity.
 */
Entity ColliderCube(const Ref<Scene>& scene, vec3 position, vec3 size);

/**
 * @brief Creates a new entity with with a Light component - directional and a model to visualize it.
 *
 * @param scene The scene to create the entity in.
 * @param rotation The rotation of the light.
 * @param intensity The intensity of the light.
 * @return The created entity.
 */
Entity DirectionalLight(const Ref<Scene>& scene, const vec3& rotation, float intensity = 1.0);

/**
 * @brief Creates a new entity with with a Light component - point and a model to visualize it.
 *
 * @param scene The scene to create the entity in.
 * @param position The position of the light.
 * @param intensity The intensity of the light.
 * @return The created entity.
 */
Entity PointLight(const Ref<Scene>& scene, const vec3& position, float intensity = 1.0);

/**
 * @brief Creates a new entity with with a Light component - spot and a model to visualize it.
 *
 * @param scene The scene to create the entity in.
 * @param position The position of the light.
 * @param rotation The rotation of the light.
 * @param intensity The intensity of the light.
 * @return The created entity.
 */
Entity SpotLight(const Ref<Scene>& scene, const vec3& position, const vec3& rotation, float intensity = 1.0);

};  // namespace Entities

}  // namespace labeeri::Engine
