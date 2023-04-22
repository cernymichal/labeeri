#pragma once

#include "../IRenderable.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class MenuWindow : public IRenderable {
public:
    /**
     * @brief TODO
     */
    MenuWindow();

    /**
     * @brief TODO
     */
    void render() override;

private:
    bool m_VSync = true;
};

}  // namespace labeeri::engine
