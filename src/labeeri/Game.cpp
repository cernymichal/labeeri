#include "Game.h"

#include "../engine.h"
#include "scenes.h"

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto [scene, camera] = defaultScene();
    LAB_CURRENT_SCENE = scene;
    LAB_CURRENT_CAMERA = camera;
}

}  // namespace labeeri
