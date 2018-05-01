#include "rect2d.h"
#include <iostream>

Rect2D::Rect2D()
{
    loc = Point2D(0,0);
    size = Point2D(0,0);
}

Rect2D::~Rect2D()
{
    //dtor
}

bool Rect2D::intersect(Rect2D target)
{
    bool r = false;

    if (loc.x < target.loc.x + target.size.x &&
            loc.y < target.loc.y + target.size.y &&
            target.loc.x < loc.x + size.x &&
            target.loc.y < loc.y + size.y)
        r = true;

    return r;
}
