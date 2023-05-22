#pragma once

#include "Engine/API.h"

namespace labeeri::Engine {

/**
 * @brief TODO
 */
class CameraSwitcher : public IScript {
public:
    /**
     * @brief TODO
     */
    explicit CameraSwitcher(Entity player, const std::vector<Entity>& cameras = {})
        : IScript(player), m_cameras(cameras) {
    }

protected:
    virtual void onKeyboardPress(const KeyboardPressEvent& e) {
        if (e.m_key == KeyboardKey::PageUp)
            switchToStatic(m_currentCamera + 1);
        else if (e.m_key == KeyboardKey::PageDown)
            switchToStatic(m_currentCamera - 1);
        else if (e.m_key == KeyboardKey::F1) {
            if (m_freeCamera)
                switchToPlayer();
            else
                switchToFree();
        }
    }

private:
    std::vector<Entity> m_cameras;
    size_t m_currentCamera = 0;
    Entity m_freeCamera = NULL_ENTITY;
    Collider m_playerCollider;

    void switchToStatic(size_t index) {
        if (m_cameras.size() == 0)
            return;

        m_currentCamera = (index + m_cameras.size()) % m_cameras.size();

        if (m_freeCamera)
            m_freeCamera.destroy();

        switchPlayerMovement(false);

        LAB_CURRENT_CAMERA = m_cameras[m_currentCamera];
    }

    void switchToPlayer() {
        if (m_freeCamera)
            m_freeCamera.destroy();

        switchPlayerMovement(true);

        LAB_CURRENT_CAMERA = m_entity;
    }

    void switchToFree() {
        switchPlayerMovement(false);

        m_freeCamera = Entities::Flycam(LAB_CURRENT_SCENE);
        *m_freeCamera.getComponent<Transform>() = *LAB_CURRENT_CAMERA.getComponent<Transform>();
        LAB_CURRENT_CAMERA = m_freeCamera;
    }

    void switchPlayerMovement(bool enable) {
        auto collider = m_entity.getComponent<Collider>();
        if (enable)
            *collider = m_playerCollider;
        else {
            m_playerCollider = *collider;
            collider->m_extents *= 0.0f;
        }

        m_entity.getComponent<RigidBody>()->m_static = !enable;
    }
};

}  // namespace labeeri::Engine
