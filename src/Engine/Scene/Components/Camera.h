#pragma once

#include "Engine/Scene/Components/Transform.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class Camera {
public:
    float m_FOV;
    float m_near;
    float m_far;
    bool m_crosshair;

    explicit Camera(bool crosshair = false, float FOV = 90.0f, float near = 0.1f, float far = std::numeric_limits<float>::infinity())
        : m_crosshair(crosshair), m_FOV(FOV), m_near(near), m_far(far) {
    }

    /**
     * @brief TODO
     */
    mat4 viewMatrix(const Transform& transform) const {
        vec3 cameraPosition = transform.worldPosition();
        vec3 center = cameraPosition + transform.forward();

        return glm::lookAt(cameraPosition, center, transform.up());
    }

    /**
     * @brief TODO
     */
    mat4 projectionMatrix(uvec2 viewportSize) const {
        float aspectRatio = (float)viewportSize.x / (float)viewportSize.y;

        if (m_far != std::numeric_limits<float>::infinity())
            return glm::perspectiveZO(glm::radians(m_FOV), aspectRatio, m_far, m_near);  // Z reversed

        float f = 1.0f / tan(glm::radians(m_FOV) / 2.0f);
        return mat4(
            f / aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, m_near, 0.0f);
    }
};

}  // namespace labeeri::Engine
