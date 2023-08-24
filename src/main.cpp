#include "Engine/Application.h"
#include "Engine/Resources/Resources.h"
#include "Game/Game.h"

extern "C" {
// Hint to aquire a dedicated GPU on laptops
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;  // NVIDIA
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;    // AMD
}

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
