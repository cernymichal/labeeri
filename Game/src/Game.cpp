#include "Game.h"

#include "Scenes.h"

void Game::setup() {
    Ref<Scene> scene = loadLabyrinthScene();

    LAB_APP.setScene(scene);
}
