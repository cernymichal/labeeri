#include "Game.h"

#include "scenes.h"

#define CURRENT_SCENE m_app.m_scene
#define CURRENT_CAMERA m_app.camera()

namespace labeeri {

Game::Game(engine::Application& app) : m_app(app) {
}

void Game::setup() {
    auto [scene, camera] = defaultScene();
    CURRENT_SCENE = scene;
    CURRENT_CAMERA = camera;
}

}  // namespace labeeri
