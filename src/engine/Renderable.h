#pragma once

namespace labeeri::engine {

class Application;

/**
 * @brief TODO
 */
class Renderable {
public:
    /**
     * @brief TODO
     */
    Renderable(Application& app) : m_app(app) {
    }

    /**
     * @brief TODO
     */
    virtual void render() = 0;

protected:
    Application& m_app;
};

}  // namespace labeeri::engine
