#include "Game.h"

#include "Engine/API.h"
#include "Game/Scenes.h"

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = defaultScene();

    auto flycam = Engine::Entities::Flycam();
    flycam->transform()->move(glm::vec3(0.0, 2.5, 0.0));
    scene->addEntity(flycam);

    LAB_CURRENT_SCENE = scene;
    LAB_CURRENT_CAMERA = flycam->m_camera;
}

}  // namespace labeeri
