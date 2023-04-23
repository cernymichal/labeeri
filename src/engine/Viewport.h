#pragma once

#include "IRenderable.h"
#include "scene/Camera.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class Viewport : public IRenderable {
public:
    std::shared_ptr<Camera> m_camera;

    /**
     * @brief TODO
     */
    Viewport();

    /**
     * @brief TODO
     */
    void render() override;

    /**
     * @brief TODO
     */
    void resize(int width, int height);
};

}  // namespace labeeri::engine
