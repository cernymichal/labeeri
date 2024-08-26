#include "Game.h"

#include <Engine/API.h>

#include "Scenes.h"

namespace labeeri {

void Game::setup() {
    auto scene = loadLabyrinthScene();

    LAB_APP.setScene(scene);
}

}  // namespace labeeri
