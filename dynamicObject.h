#pragma once

#include "gameObject.h"

class DynamicObject : public GameObject
{
    Q_OBJECT
protected:
    int velocity;
    QTimer* timer;
public:
    enum Direction { Right, Up, Left, Down};

protected:
    Direction dir;

public:
    DynamicObject(int v = 0, Direction d = Up) : velocity(v), dir(d) {};

    // getters
    inline int v() const { return velocity; }
    inline Direction d() const { return dir; }

    // setters
    virtual void setVel(int v);    
    void setDir(Direction d);

public slots:
    void move();
};