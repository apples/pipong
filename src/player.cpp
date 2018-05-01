#include "player.h"

Player::Player()
{
    loc = Point2D(0,0);
    vel = Point2D(0,0);
    acc = Point2D(0,0);
    size = Point2D(0,0);

    side = 0;
    score = 0;
    controlType = 0;

    texture = 0;
}

Player::~Player()
{
    //dtor
}

void Player::accel(Point2D a)
{
    acc = acc + a;
}

void Player::addScore(int s)
{
    score += s;
}

void Player::update()
{
    loc = loc + vel;
    vel = vel + acc;
    acc = Point2D(0,0);

    if (loc.y - size.y < 30)
    {
        vel.y = 0;
        loc.y = 30 + size.y;
    }

    if (loc.y + size.y > 570)
    {
        vel.y = 0;
        loc.y = 570 - size.y;
    }
}

void Player::resetDim()
{
    if (side == 1)
    {
        loc.x = 30;
    }
    else
    {
        loc.x = 770;
    }

    loc.y = 300;

    vel.x = 0;
    vel.y = 0;

    acc.x = 0;
    acc.y = 0;

    size.x = 8;
    size.y = 32;
}

void Player::resetAll()
{
    resetDim();

    score = 0;
}

void Player::drawMe()
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

void Player::setTexture(GLuint tex)
{
    texture = tex;
}

Rect2D Player::getRect()
{
    Rect2D r;
    r.loc = Point2D(loc.x-size.x, loc.y-size.y);
    r.size = Point2D(size.x*2, size.y*2);

    return r;
}
