#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glfw.h>
#include "point2d.h"
#include "rect2d.h"

class Player
{
public:
    Player();
    virtual ~Player();

    GLuint texture;

    Point2D loc;
    Point2D vel;
    Point2D acc;
    Point2D size;

    int side;
    int score;
    int controlType;

    void accel(Point2D a);
    void addScore(int s);

    void update();

    void resetDim();
    void resetAll();

    void setTexture(GLuint tex);
    void drawMe();

    Rect2D getRect();
};

#endif // PLAYER_H
