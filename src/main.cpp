#include "Engine/Application.h"
#include "Engine/Resources/Resources.h"
#include "Game/Game.h"

int main(int argc, char** argv) {
    LAB_APP.initialize();

    // while (!LAB_APP.closed()) {
    try {
        labeeri::Game game;
        game.setup();
        LAB_APP.run();
    }
    catch (const std::exception& e) {
        LAB_LOGH1("EXCEPTION CAUGHT");
        LAB_LOG(e.what());
    }
    //}

    return EXIT_SUCCESS;
}
