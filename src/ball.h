#ifndef BALL_H
#define BALL_H

#include <GL/glfw.h>
#include "point2d.h"
#include "rect2d.h"

class Ball
{
public:
    Ball();
    virtual ~Ball();

    Point2D loc;
    Point2D vel;
    Point2D acc;
    Point2D size;

    GLuint texture;

    void accel(Point2D a);

    void update(float m);

    void resetDim();

    void drawMe();
    void setTexture(GLuint tex);

    Rect2D getRect();
};

#endif // BALL_H
