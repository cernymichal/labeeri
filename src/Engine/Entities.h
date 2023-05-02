#pragma once

#include "Engine/Scene/Entity.h"

namespace labeeri::Engine {

namespace Entities {

/**
 * @brief TODO
 */
EntityRef Flycam(float speed = 4.0, double sensitivity = 0.002);

EntityRef DirectionalLight(const glm::vec3& rotation, float intensity = 1.0);

EntityRef PointLight(const glm::vec3& position, float intensity = 1.0);

EntityPack SpotLight(const glm::vec3& position, const glm::vec3& rotation, float intensity = 1.0);

};  // namespace Entities

}  // namespace labeeri::Engine
