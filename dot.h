#pragma once

#include "gameObject.h"

class Dot : public GameObject
{
public:
    //const int normalSize = 8;
    //const int bigSize = 14;
    enum type { normal = 4, big = 14};

    type dotType;

    Dot() : GameObject(0, 0, 0, 0), dotType(normal) {};
    Dot(int x, int y, type t);
    Dot(Dot& d);

    void setBigDot(QPoint p);
    void setNormalDot(QPoint p);
};
