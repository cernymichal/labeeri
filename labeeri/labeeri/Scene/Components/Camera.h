#pragma once

#include "Scene/Components/Transform.h"

namespace labeeri {

/**
 * @brief Component describin a camera. Entity with this component is used as the viewport camera.
 *
 * Far plane at infinity is supported.
 * Uses reversed-Z for depth buffer.
 */
class Camera {
public:
    f32 m_FOV;
    f32 m_near;
    f32 m_far;
    bool m_crosshair;

    // TODO cache matrices

    explicit Camera(bool crosshair = false, f32 FOV = 90.0f, f32 near = 0.1f, f32 far = std::numeric_limits<f32>::infinity())
        : m_crosshair(crosshair), m_FOV(FOV), m_near(near), m_far(far) {
    }

    /**
     * @brief Calculates a view matrix for the camera and the passed transforms location.
     *
     * @param transform Transform of the camera.
     * @return The calculated view matrix.
     */
    mat4 viewMatrix(const Transform& transform) const {
        return transform.modelMatrixInverse();
    }

    /**
     * @brief Calculates a projection matrix for the camera and the passed viewport size.
     *
     * @param viewportSize Size of the viewport in pixels.
     * @return The calculated projection matrix.
     */
    mat4 projectionMatrix(uvec2 viewportSize) const {
        f32 aspectRatio = (f32)viewportSize.x / (f32)viewportSize.y;

        if (m_far != std::numeric_limits<f32>::infinity())
            return glm::perspectiveZO(glm::radians(m_FOV), aspectRatio, m_far, m_near);  // reversed Z

        f32 f = 1.0f / tan(glm::radians(m_FOV) / 2.0f);
        return mat4(
            f / aspectRatio, 0.0f, 0.0f, 0.0f,
            0.0f, f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, -1.0f,
            0.0f, 0.0f, m_near, 0.0f);
    }
};

}  // namespace labeeri
