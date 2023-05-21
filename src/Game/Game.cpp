#include "Game.h"

#include "Engine/API.h"
#include "Game/Scenes.h"

using namespace labeeri::Engine;

namespace labeeri {

Game::Game() {
}

void Game::setup() {
    auto scene = Scenes::showcase();

    LAB_APP.setScene(scene);
}

}  // namespace labeeri
