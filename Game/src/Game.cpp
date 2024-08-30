#include "Game.h"

#include "Scenes.h"

void Game::setup() {
    //auto scene = loadLabyrinthScene();

    LAB_APP.setScene(labeeri::Scenes::showcase());
}
