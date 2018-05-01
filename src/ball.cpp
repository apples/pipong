#include "ball.h"

Ball::Ball()
{
    loc = Point2D(0,0);
    vel = Point2D(0,0);
    acc = Point2D(0,0);
    size = Point2D(0,0);

    texture = 0;
}

Ball::~Ball()
{
    //dtor
}

void Ball::accel(Point2D a)
{
    acc.x += a.x;
    acc.y += a.y;
}

void Ball::update(float m)
{
    loc.x += vel.x * m;
    loc.y += vel.y * m;

    if (loc.y - size.y < 30)
    {
        vel.y = -vel.y;
        loc.y = 30 + size.y;
    }

    if (loc.y + size.y > 570)
    {
        vel.y = -vel.y;
        loc.y = 570 - size.y;
    }
}

void Ball::resetDim()
{
    loc = Point2D(400,300);

    vel = Point2D(0,0);

    acc = Point2D(0,0);

    size = Point2D(8,8);
}

void Ball::drawMe()
{
    glPushMatrix();

    glTranslatef(loc.x, loc.y, 0);

    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(-size.x, -size.y);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(size.x, -size.y);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(size.x, size.y);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(-size.x, size.y);
    glEnd();

    glPopMatrix();
}

void Ball::setTexture(GLuint tex)
{
    texture = tex;
}

Rect2D Ball::getRect()
{
    Rect2D r;
    r.loc = Point2D(loc.x-size.x, loc.y-size.y);
    r.size = Point2D(size.x*2, size.y*2);

    return r;
}
