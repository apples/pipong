
#include <GL/glfw.h>
#include "game.h"

#include <string>

extern Game game = Game();

int main(int argc, char* argv[])
{
    game.init(800, 600);
    game.load();

    game.p1ai = false;
    game.p2ai = true;

    for(int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-p1ai") {
            std::string parg = argv[i+1];
            if (parg == "true") {
                game.p1ai = true;
            }
        }
        if (arg == "-p2ai" && i+1 < argc) {
            std::string parg = argv[i+1];
            if (parg != "true") {
                game.p2ai = false;
            }
        }
    }

    while (game.running) {
        game.reset();
        game.gameLoop();
    }

    return 0;
}
