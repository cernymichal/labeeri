#include "Game.h"

#include "../engine.h"
#include "scenes.h"

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = defaultScene();

    auto flycam = engine::Entities::Flycam();
    scene->addEntity(flycam);

    LAB_CURRENT_SCENE = scene;
    LAB_CURRENT_CAMERA = flycam->m_camera;
}

}  // namespace labeeri
