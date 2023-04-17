#pragma once

class Application;

/**
 * @brief TODO
 */
class Renderable {
public:
    /**
     * @brief TODO
     */
    Renderable(Application& application) : m_application(application) {
    }

    /**
     * @brief TODO
     */
    virtual void render() = 0;

protected:
    Application& m_application;
};
