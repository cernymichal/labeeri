#pragma once

#include "../Renderable.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class MenuWindow : public Renderable {
public:
    /**
     * @brief TODO
     */
    MenuWindow(Application& app);

    /**
     * @brief TODO
     */
    void render() override;

private:
    bool m_VSync = true;
};

}  // namespace labeeri::engine
