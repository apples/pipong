#include "point2d.h"

Point2D::Point2D()
{
    x = 0;
    y = 0;
}

Point2D::Point2D(float nx, float ny)
{
    x = nx;
    y = ny;
}

Point2D Point2D::operator+(Point2D rhp)
{
    return Point2D(x+rhp.x, y+rhp.y);
}

Point2D Point2D::operator-(Point2D rhp)
{
    return Point2D(x-rhp.x, y-rhp.y);
}

Point2D Point2D::operator*(float rhp)
{
    return Point2D(x*rhp, y*rhp);
}

bool Point2D::liesWithin(Point2D loc, Point2D size)
{
    bool r=false;

    if (x < loc.x + size.x &&
            y < loc.y + size.y &&
            x > loc.x &&
            y > loc.y)
        r = true;

    return r;
}
