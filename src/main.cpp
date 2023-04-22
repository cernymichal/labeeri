#include "engine/Application.h"
#include "labeeri/Game.h"

int main(int argc, char** argv) {
    while (!LAB_APP.closed()) {
        try {
            labeeri::Game game;
            game.setup();
            LAB_APP.run();
        }
        catch (const std::exception& e) {
            LAB_LOGH1("EXCEPTION CAUGHT");
            LAB_LOG(e.what());
        }
    }

    return EXIT_SUCCESS;
}
