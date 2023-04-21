#pragma once

#include "../Renderable.h"

namespace labeeri::engine {

/**
 * @brief TODO
 */
class LogWindow : public Renderable {
public:
    /**
     * @brief TODO
     */
    LogWindow(Application& app);

    /**
     * @brief TODO
     */
    void render() override;

private:
    bool m_autoScroll = true;
};

}  // namespace labeeri::engine
