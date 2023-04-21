#include <iostream>

#include "labeeri/Game.h"

int main(int argc, char** argv) {
    labeeri::engine::Application app;

    while (!app.closed()) {
        try {
            labeeri::Game game(app);
            game.setup();
            app.run();
        }
        catch (const std::exception& e) {
            LAB_LOGH1("EXCEPTION CAUGHT");
            LAB_LOG(e.what());
        }
    }

    LAB_LOG_OGL_ERROR();
    LAB_DEBUG_ONLY(std::cout << LAB_LOGSTREAM_STR << std::endl);

    return EXIT_SUCCESS;
}
