#ifndef GAME_H
#define GAME_H

#include <GL/glfw.h>
#include "game.h"
#include "player.h"
#include "ball.h"
#include "bitmapfont.h"
#include "frameratecounter.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void win();
    void lose();

    int init(int w, int h);
    int load();
    int reset();

    int gameLoop();

    int windowWidth, windowHeight;

    Player p1, p2;

    BitmapFont font;

    Ball ball;

    FramerateCounter fpsCounter;

    bool	    running;
    GLuint      sprites[7];

    bool p1ai, p2ai;
};

#endif // GAME_H
