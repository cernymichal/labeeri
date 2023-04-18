#pragma once

#include "../Renderable.h"

/**
 * @brief TODO
 */
class MenuWindow : public Renderable {
public:
    /**
     * @brief TODO
     */
    MenuWindow(Application& application);

    /**
     * @brief TODO
     */
    void render() override;

private:
    bool m_VSync = true;
};
