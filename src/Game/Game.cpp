#include "Game.h"

#include "Engine/API.h"
#include "Game/Scenes.h"

using namespace labeeri::Engine;

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = defaultScene();

    auto flycam = Entities::Flycam(*scene);
    flycam.getComponent<Transform>(*scene->ecs())->move(glm::vec3(0.0, 2.5, 0.0));

    LAB_APP.setScene(scene);
    LAB_CURRENT_CAMERA = flycam;
}

}  // namespace labeeri
