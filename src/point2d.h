#ifndef POINT2D_H
#define POINT2D_H

struct Point2D
{
    Point2D();
    Point2D(float nx, float ny);

    float x;
    float y;

    Point2D operator+(Point2D);
    Point2D operator-(Point2D);

    Point2D operator*(float);

    bool liesWithin(Point2D loc, Point2D size);
};

#endif // POINT2D_H
