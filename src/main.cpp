#include "Engine/Application.h"
#include "Engine/Resources/Resources.h"
#include "Game/Game.h"

extern "C" {
// Hint to aquire a dedicated GPU on laptops
__declspec(dllexport) u64 NvOptimusEnablement = 0x00000001;  // NVIDIA
__declspec(dllexport) i32 AmdPowerXpressRequestHighPerformance = 1;    // AMD
}

i32 main(i32 argc, char** argv) {
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
