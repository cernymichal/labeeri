#include "Game.h"

#include "Engine/API.h"
#include "Game/Scenes.h"

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = defaultScene();

    auto flycam = Engine::Entities::Flycam();
    scene->addEntity(flycam);

    LAB_CURRENT_SCENE = scene;
    LAB_CURRENT_CAMERA = flycam->m_camera;
}

}  // namespace labeeri
