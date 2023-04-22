#pragma once

#include "../IRenderable.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class LogWindow : public IRenderable {
public:
    /**
     * @brief TODO
     */
    LogWindow();

    /**
     * @brief TODO
     */
    void render() override;

private:
    bool m_autoScroll = true;
};

}  // namespace labeeri::engine
