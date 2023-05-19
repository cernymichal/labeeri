#pragma once

#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Camera {
public:
    float m_FOV = 90.0f;
    float m_near = 0.1f;
    float m_far = std::numeric_limits<float>::infinity();

    /**
     * @brief TODO
     */
    glm::mat4 viewMatrix(const Transform& transform) const {
        glm::vec3 cameraPosition = transform.worldPosition();
        glm::vec3 center = cameraPosition + transform.forward();

        return glm::lookAt(cameraPosition, center, transform.up());
    }

    /**
     * @brief TODO
     */
    glm::mat4 projectionMatrix(glm::uvec2 viewportSize) const {
        float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

        if (m_far != std::numeric_limits<float>::infinity())
            return glm::perspectiveZO(glm::radians(m_FOV), aspectRatio, m_far, m_near);  // Z reversed

        float f = 1.0f / tan(glm::radians(m_FOV) / 2.0f);
        return glm::mat4(
            f / aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, m_near, 0.0f);
    }
};

}  // namespace labeeri::Engine
