#include "Game.h"

#include "Engine/API.h"
#include "Game/Scenes.h"

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = loadLabyrinthScene();

    LAB_APP.setScene(scene);
}

}  // namespace labeeri
