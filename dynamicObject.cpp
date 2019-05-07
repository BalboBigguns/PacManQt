#include "dynamicObject.h"

void DynamicObject::setVel(int v)
{
    if (v >= 0) {
        velocity = v;
    }
} 

void DynamicObject::setDir(Direction d)
{
    dir = d;
}

void DynamicObject::move()
{
    switch(dir) {
    case Up:
        pos.setY(pos.y() - velocity);
        break;
    case Down:
        pos.setY(pos.y() + velocity);
        break;
    case Left:
        pos.setX(pos.x() - velocity);
        break;
    case Right:
        pos.setX(pos.x() + velocity);
        break;
    }

    //printf("%d, %d\n", pos.x(), pos.y());           // DEBUG TIME
}