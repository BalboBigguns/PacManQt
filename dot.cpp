#include "dot.h"

Dot::Dot(int x, int y, type t)
{
    setX(x);
    setY(y);
    dotType = t;
    if (dotType == big) {
        setWidth(big);
        setHeight(big);
    }
    else {
        setWidth(normal);
        setHeight(normal);
    }
}

Dot::Dot(Dot& d) : GameObject(d)
{
    dotType = d.dotType;
}

void Dot::setBigDot(QPoint p)
{
    pos = p;
    dotType = big;
    setWidth(big);
    setHeight(big);
}

void Dot::setNormalDot(QPoint p)
{
    pos = p;
    dotType = normal;
    setWidth(normal);
    setHeight(normal);
}